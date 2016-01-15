#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>

int main(void)
{
	const int p = 500;
	float *x = malloc(p * sizeof *x);
	float *y = malloc(p * sizeof *y);
	float *orig = malloc(p * sizeof *orig);
	int i;

	if (!(x && y && orig)) {
		perror("malloc");
		exit(1);
	}

	for (i = 0; i < p; ++i) {
		y[i] = i;
		x[i] = 2 * i;
	}
	cblas_scopy(p, y, 1, orig, 1);
	cblas_saxpy(p, -1, x, 1, y, 1);
	for (i = 0; i < p; ++i)
		printf("y(%f) - x(%f) = %f\n", orig[i], x[i], y[i]);

	return 0;
}
