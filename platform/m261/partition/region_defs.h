#ifndef __REGION_DEFS_H__
#define __REGION_DEFS_H__

#define IMAGE_CODE_SIZE (0x8000)

#define ROM_ALIAS_BASE  (0x00000000)
#define RAM_ALIAS_BASE  (0x20000000)

#define ROM_ALIAS(x)  (ROM_ALIAS_BASE + (x))
#define RAM_ALIAS(x)  (RAM_ALIAS_BASE + (x))

#define CODE_START  (ROM_ALIAS(IMAGE_OFFSET))
#define CODE_SIZE   (IMAGE_CODE_SIZE)
#define DATA_START  (RAM_ALIAS(0x0))

#endif