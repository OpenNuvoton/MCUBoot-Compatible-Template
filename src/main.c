#include <stdio.h>
#include "platform.h"

int main(void)
{
    platform_init();

    printf("Hello World from %s\n", xstr(PLATFORM_NAME));
    printf("This is slot %s\n", xstr(SLOT_NUM));

    while(1);
}
