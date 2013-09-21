/* diffidx - demo SSE 4.2 string comparison
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CPUID_SSE4_2_BIT (20)

extern unsigned long diffidx(char *, char *, size_t);
extern unsigned long cpuidfn(unsigned long);

void loadstr(char *buf, char *s, size_t m)
{
	size_t n;

	memset(buf, 0, m);
	n = strlen(s);
	if (n > m)
		n = m;
	memmove(buf, s, n);
}

int main(int argc, char *argv[])
{
	unsigned long n = (unsigned long) cpuidfn(1);
	char a[512] = "0123456789abcdef";	/* 128-bits worth of data */
	char b[512] = "01c3456789abCdef";
	size_t alen = strlen(a);
	size_t blen = strlen(b);

	if ((n >> CPUID_SSE4_2_BIT & 1) == 0) {
		fputs("cpuid says this CPU hasn't SSE 4.2\n", stderr);
		exit(1);
	}
	if (argc > 1) {
		loadstr(a, argv[1], sizeof a - 1);
		alen = strlen(a);
	}
	if (argc > 2) {
		loadstr(b, argv[2], sizeof b - 1);
		blen = strlen(b);
	}
	printf("\"%s\" and \"%s\" differ at byte index %lu\n",
	       a, b, diffidx(a, b, alen > blen ? blen : alen));

	return 0;
}
