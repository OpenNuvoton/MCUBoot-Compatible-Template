#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include "NuMicro.h"

#define xstr(a) str(a)
#define str(a) #a

int32_t platform_init(void);

#endif