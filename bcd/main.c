#include <stdio.h>

extern void bcddemo(unsigned char *, unsigned char *);

// For the ten bytes, least significant comes first.
// For the two nibbles in each byte, the most significant nibble
//   is the most significant decimal digit.
void pr(unsigned char *bcd)
{
	int i;

	for (i = 9; i >= 0; --i)
		printf("%d%d", bcd[i] >> 4 & 0xf, bcd[i] & 0xf);
	putchar('\n');
}

int main(void)
{
	float a = 0.1;
	float b = 0.2;
	unsigned char bcda[10] = {
		9<<4|9, 0, /* 99 (standard says 0 is repeated) */
	};
	unsigned char bcdb[10] = {
		1, 1, 0,	/* 101 */
	};
	long double aa = 0.1, bb = 0.2;

	printf("sizeof long double: %lu\n", sizeof aa);
	printf("%g + %g = %g\n", a, b, a + b);
	printf("%Lg + %Lg = %Lg\n", aa, bb, aa + bb);
	pr(bcda);
	pr(bcdb);
	bcddemo(bcda, bcdb);
	pr(bcda);

	return 0;
}
