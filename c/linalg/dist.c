#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>

int main(void)
{
	const int p = 10;
	float *x = malloc(p * sizeof *x);
	float *y = malloc(p * sizeof *y);
	float *z = malloc(p * sizeof *y);
	float *orig = malloc(p * sizeof *orig);
	int i;

	if (!(x && y && orig && z)) {
		perror("malloc");
		exit(1);
	}

	for (i = 0; i < p; ++i) {
		y[i] = i;
		x[i] = 2 * i;
		z[i] = 0;
	}
	cblas_scopy(p, y, 1, orig, 1);
	cblas_saxpy(p, -1, x, 1, y, 1);

	/* There's GEMV, but you have to put one vector into the
	 * diagonal of a matrix because... uh...
	 * Somethin'?
	 *
	 * But WAIT!  It's not stupid because there are compact
	 * ways to represent banded matrices, and a diagonal matrix
	 * can be represented by a single row, kind of like it
	 * was a ... VECTOR!?!?!?
	 *
	 * <neo>Whoa.</neo>
	 */
	cblas_sgbmv(CblasRowMajor,
		    CblasNoTrans, /* Don't transpose A */
		    p, p,
		    0,		/* bands below the diagonal */
		    0,		/* bands above the diagonal */
		    1,		/* alpha */
		    y,		/* some data, at last! */
		    1,		/* LDA is 1st dim of A */
		    y,
		    1,
		    1,
		    z,
		    1);
	for (i = 0; i < p; ++i) {
		printf("y(%f) - x(%f) = %f\n", orig[i], x[i], y[i]);
		printf("(y-x)^2 = %f\n", z[i]);
	}
	return 0;
}
