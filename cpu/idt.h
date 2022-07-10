#ifndef OS_IDT_H
#define OS_IDT_H

#include "../kernel/types.h"

typedef struct {
    u16int limit;           // Limit (8 * 32 - 1)
    u32int base ;           // Base
} __attribute__((packed)) idtr_t;

typedef struct {
    u16int low;             // offset bits 0..15
    u16int selector;        // 0x08
    u8int  zero;            // unused, set to 0
    u8int  type;            // gate type, dpl, and p fields
    u16int high;            // offset bits 16..31
} __attribute__((packed)) idt_t;

void init_idt();
void set_idt(int vector, u32int offset);

extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

#endif
