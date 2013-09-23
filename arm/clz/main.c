#include <stdio.h>

extern int clz(int);

int main(void)
{
	printf("%d\n", clz(1<<9));
	return 0;
}
