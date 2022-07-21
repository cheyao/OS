#ifndef OS_ISR_H
#define OS_ISR_H

#include "kernel/types.h"


void int_handler(u8int int_no, u8int err_code);
void irq_handler(u8int int_no, u8int err_code);

typedef void (*isr_t)(u8int int_no);
void register_interrupt_handler(u8int n, isr_t handler);

#endif //OS_ISR_H
