#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

struct perthread {
	pthread_t tinfo;
	uint32_t count;
};
struct tinfo {		/* per-thread data with padding */
	union {
		struct perthread t;
		char pad[64];
	};
};

enum {
	MUTEX,			/* use pthread mutex and shared counter */
	LKADDSH,		/* locked add on shared counter */
	LKADDNO,		/* locked add on non-shared counter */
	ADDNO,			/* non-locked add on non-shared counter */
};
static int type;
static uint32_t count;
static pthread_mutex_t mutex;
static long int niters;

static void *
dowork(void *data)
{
	int i;
	struct tinfo *ti = (struct tinfo *) data;

	switch (type) {
	case LKADDSH:
		for (i = 0; i < niters; ++i)
			asm volatile("lock; addq $1, %0"
				     : "=m" (count)
				     : "m" (count));
		break;
	case LKADDNO:
		for (i = 0; i < niters; ++i)
			asm volatile("lock; addq $1, %0"
				     : "=m" (ti->t.count)
				     : "m" (ti->t.count));
		break;
	case ADDNO:
		for (i = 0; i < niters; ++i)
			ti->t.count += 1;
		break;
	case MUTEX:
	default:
		for (i = 0; i < niters; ++i) {
			pthread_mutex_lock(&mutex);
			count++;
			pthread_mutex_unlock(&mutex);
		}
		break;
	}

	return data;
}

int main(int argc, char *argv[])
{
	struct tinfo *a;
	long int n;
	int i;
	char *end;

	n = 10;
	if (argc > 1) {
		n = strtol(argv[1], &end, 0);
		if (end == argv[1])
			exit(EXIT_FAILURE);
	}

	niters = 10000;
	if (argc > 2) {
		niters = strtol(argv[2], &end, 0);
		if (end == argv[2])
			exit(EXIT_FAILURE);
	}

	type = MUTEX;
	if (argc > 3) {
		type = (int) strtol(argv[3], &end, 0);
		if (end == argv[3])
			exit(EXIT_FAILURE);
	}

	printf("%ld threads for %ld iterations, test type %d\n",
	       n, niters, type);
	if (pthread_mutex_init(&mutex, NULL)) {
		perror("pthread_mutex_init");
		exit(EXIT_FAILURE);
	}
	a = malloc(n * sizeof *a);
	if (!a) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < n; ++i)
		if (pthread_create(&a[i].t.tinfo, NULL, dowork, &a[i])) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	for (i = 0; i < n; ++i) {
		if (pthread_join(a[i].t.tinfo, NULL)) {
			perror("pthead_join");
			exit(EXIT_FAILURE);
		}
		if (type == LKADDNO || type == ADDNO)
			count += a[i].t.count;
	}
	pthread_mutex_destroy(&mutex);
	free(a);

	printf("%s: resulting count is %lu\n",
	       (n * niters) == count ? "OK" : "WRONG",
	       (unsigned long) count);

	return 0;
}
