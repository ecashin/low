/* Intel Software Developers Manual 3.7 says immediate value limited
 * to 2^32 but only has example with eax.  What about rax?
 */
#include <stdio.h>

extern unsigned long bigimm(unsigned long);

int main(void)
{
	printf("got 0x%lx, expected 0x%lx\n", bigimm(1), (1UL<<32)+101);

	return 0;
}
