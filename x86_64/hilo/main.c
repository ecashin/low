#include <stdio.h>

extern unsigned long hilo(unsigned long);

int main(void)
{
	unsigned long n = 1<<8|2;
	unsigned long m;

	m = n >> 8 & 0xff;
	m |= n & 0xff;
	printf("got 0x%lx, expected 0x%lx\n", hilo(n), m);

	return 0;
}
