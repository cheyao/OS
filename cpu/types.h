//
// Created by Cyao1234 on 30.06.2022.
//

#ifndef OS_TYPES_H
#define OS_TYPES_H

typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;


#define low_16(address) (u16int)((address) & 0xFFFF)
#define high_16(address) (u16int)(((address) >> 16) & 0xFFFF)

#endif
