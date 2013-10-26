#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

enum {
	MUTEX,
	LKADD,
};

static uint32_t count;
static pthread_mutex_t mutex;
static long int niters;
static int type = MUTEX;

static void *
dowork(void *data)
{
	int i;

	switch (type) {
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
	printf("%ld threads for %ld iterations\n", n, niters);
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
	return 0;
}
