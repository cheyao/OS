#ifndef OS_TIMER_H
#define OS_TIMER_H

#include "../kernel/types.h"

void init_timer(u32int freq);
void timer_wait(u32int ticks);

#endif //OS_TIMER_H
