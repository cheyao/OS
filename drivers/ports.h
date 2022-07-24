#ifndef PORTS_H
#define PORTS_H

#include "kernel/types.h"

unsigned char inb (u16int port);
void outb (u16int port, u8int data);
unsigned short inw (u16int port);
void outw (u16int port, u16int data);

#endif
