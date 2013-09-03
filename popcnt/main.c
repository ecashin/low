#include <stdio.h>
#include <stdint.h>
#include "subs.h"

#define CPUID_POPCNT_BIT (23)

int main(void)
{
	int i;
	unsigned j;
	unsigned long n = (unsigned long) cpuidfn(1);
	uint16_t a[10000];
	

	if ((n >> CPUID_POPCNT_BIT & 1) == 0) {
		return 1;
		fprintf(stderr, "no POPCNT support in CPU\n");
	}
	for (i = 0, n = 0; i < sizeof a / sizeof a[0]; ++i) {
		a[i] = i;
		j = i;
		while (j) {
			n += j & 1;
			j >>= 1;
		}
	}
	printf("initialized array with total of %lu bits set\n", n);

	n = countbits(a, sizeof a); /* note byte count in 2nd param */
	printf("countbits reports total of %lu bits set\n", n);

	return 0;
}
