/* rtmdemo - try Intel restricted transactional memory instructions
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long rtminit(void);
extern unsigned long rtmxbegin(void);
extern unsigned long rtmxend(void);
extern unsigned long rtmabortcnt(void);

int main(void)
{
	unsigned long ret;

	ret = rtminit();
	printf("rtminit:%lu\n", ret);
	if (ret)
		return 1;
	ret = rtmabortcnt();
	printf("rtmabortcnt:%lu\n", ret);
	rtmxbegin();
	puts("begun");
	rtmxend();
	puts("ended");

	return 0;
}
