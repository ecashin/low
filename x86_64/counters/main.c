#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

enum {
	MUTEX,
	LKADD,
};
static int type;
static uint32_t count;
static pthread_mutex_t mutex;
static long int niters;

static void *
dowork(void *data)
{
	int i;

	switch (type) {
	case LKADD:
		for (i = 0; i < niters; ++i)
			asm volatile("lock; addq $1, %0"
				     : "=m" (count)
				     : "m" (count));
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
	pthread_t *a;
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
		if (pthread_create(&a[i], NULL, dowork, &a[i])) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	for (i = 0; i < n; ++i)
		if (pthread_join(a[i], NULL)) {
			perror("pthead_join");
			exit(EXIT_FAILURE);
		}
	pthread_mutex_destroy(&mutex);
	free(a);

	printf("%s: resulting count is %lu\n",
	       (n * niters) == count ? "OK" : "WRONG",
	       (unsigned long) count);

	return 0;
}
