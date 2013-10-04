/* rtmdemo - try Intel restricted transactional memory instructions
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long rtminit(void);
extern unsigned long rtm(void);

int main(void)
{
	printf("%lu\n", rtminit());
	printf("%lu\n", rtm());

	return 0;
}
