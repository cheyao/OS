#ifndef OS_TYPES_H
#define OS_TYPES_H

typedef unsigned long long   u64int;
typedef          long long   s64int;
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;


typedef _Bool bool;

#define NULL 0
#define True  1;
#define False 0;

#define low_16(address) (u16int) ((address) & 0xFFFF)
#define mid_16(address) (u16int) (((address) >> 16) & 0xFFFF)
#define high_32(address) (u32int) (((address) >> 32) & 0xFFFFFFFF)

#endif
