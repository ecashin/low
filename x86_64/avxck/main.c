#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long pxorinit(void);
extern unsigned long pxordemo(void);

int main(void)
{
	printf("%lu\n", pxorinit());
	printf("%lu\n", pxordemo());

	return 0;
}
