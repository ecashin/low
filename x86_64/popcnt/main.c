#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "subs.h"

#define CPUID_POPCNT_BIT (23)
#define CPUID_SSE4_2_BIT (20)

static inline int ifloor(int n, int d)
{
	n /= d;
	return n * d;
}

static inline int cbchar(unsigned char c)
{
	int b;

	for (b = 0; c; c >>= 1)
		b += c & 1;
	return b;
}

/* This wrapper for the assembly subroutine handles alignment. */
static inline int cntbits(uint16_t *a, size_t n)
{
	int b = 0;
	unsigned char *p = (unsigned char *) a;
	unsigned char *e;
	const int blksiz = 8; /* call countbits with 64-bit "blocks" */

	for (; n > 0 && ((unsigned long) p) % blksiz; ++p, --n) /* until aligned */
		b += cbchar(*p);
	e = &p[n];
	n = ifloor(e - p, blksiz);
	b += countbits((uint16_t *) p, n); /* this is the fast part */
	for (p += n; p < e; ++p)
		b += cbchar(*p); /* the remaining odd bytes */
	return b;
}

/* demo sets up data and runs simple tests, checking correctness */
int main(void)
{
	int i;
	unsigned j;
	unsigned long n = (unsigned long) cpuidfn(1);
	unsigned long m;
	uint16_t a[10000];
	unsigned char *p;

	if ((n >> CPUID_SSE4_2_BIT & 1) == 0 ||
	    (n >> CPUID_POPCNT_BIT & 1) == 0) {
		fprintf(stderr, "no POPCNT support in CPU\n");
		return 1;
	}

	/* initialize a while counting here for later verification of cntbits */
	for (i = 0, n = 0; i < sizeof a / sizeof a[0]; ++i) {
		j = i + 1;
		a[i] = j;
		while (j) {
			n += j & 1;
			j >>= 1;
		}
	}
	printf("initialized array with total of %lu bits set\n", n);

	m = n;
	printf("countbits with %lu bits set ... ", n);
	fflush(stdout);
	n = cntbits(a, sizeof a); /* note byte count in 2nd param */
	assert(n == m);
	puts("ok.");

	/* test without first and last byte */
	p = (unsigned char *) a;
	m = n - cbchar(p[0]) - cbchar(p[(sizeof a) - 1]);
	printf("countbits on unaligned sub-array with %lu bits set ... ", m);
	fflush(stdout);
	n = cntbits((uint16_t *)(p+1), (sizeof a) - 2);
	assert(n == m);
	puts("ok.");

	fputs("zero-length input ... ", stdout);
	fflush(stdout);
	assert(cntbits(a, 0) == 0); /* test boundary case, too */
	puts("ok.");

	return 0;
}
