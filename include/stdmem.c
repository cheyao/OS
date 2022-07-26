#include "stdmem.h"

void * memset (void *dest, int val, int len) {
    unsigned char *d = dest;
    while (len-- > NULL) *d++ = val;
    return dest;
}