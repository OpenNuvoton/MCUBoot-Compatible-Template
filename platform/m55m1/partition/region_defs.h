#ifndef __REGION_DEFS_H__
#define __REGION_DEFS_H__

#define IMAGE_CODE_SIZE (0x8000)

#define ROM_ALIAS_BASE  (0x00100000)
#define RAM_ALIAS_BASE  (0x20100000)

#define SRAM_CACHEABLE_SIZE (0x00130000)
#define HEAP_SIZE   (0x800)
#define STACK_TOP   (0x20020000)
#define STACK_SIZE  (0x800)

#define ROM_ALIAS(x)  (ROM_ALIAS_BASE + (x))
#define RAM_ALIAS(x)  (RAM_ALIAS_BASE + (x))

#ifdef DIRECT_XIP
#define CODE_START  (IMAGE_OFFSET)
#else
#define CODE_START  (ROM_ALIAS(IMAGE_OFFSET))
#endif

#define CODE_SIZE   (IMAGE_CODE_SIZE)
#define DATA_START  (RAM_ALIAS(0x0))
#define DATA_SIZE   (SRAM_CACHEABLE_SIZE - HEAP_SIZE)

#endif