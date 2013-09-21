/* diffidx - demo SSE 4.2 string comparison
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
	char a[] = "0123456789abcdef";	/* 128-bits worth of data */
	char b[] = "01c3456789abCdef";

	if ((n >> CPUID_SSE4_2_BIT & 1) == 0) {
		fputs("cpuid says this CPU hasn't SSE 4.2\n", stderr);
		exit(1);
	}
	assert(sizeof a == 2*sizeof(unsigned long) + 1 && sizeof a == sizeof b);

	if (argc > 1)
		loadstr(a, argv[1], sizeof a - 1);
	if (argc > 2)
		loadstr(b, argv[2], sizeof b - 1);
	printf("\"%s\" and \"%s\" differ at byte %lu\n",
	       a, b, diffidx(a, b, sizeof a - 1));

	return 0;
}
