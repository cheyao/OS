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

/* IRQ definitions */
extern void irq_0();
extern void irq_1();
extern void irq_2();
extern void irq_3();
extern void irq_4();
extern void irq_5();
extern void irq_6();
extern void irq_7();
extern void irq_8();
extern void irq_9();
extern void irq_10();
extern void irq_11();
extern void irq_12();
extern void irq_13();
extern void irq_14();
extern void irq_15();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

__attribute__((aligned(8)))
__attribute__((unused)) static idt_t  idt[256];   // Defines 32 idts
__attribute__((unused)) static idtr_t idtr;       // Makes a idtr


#endif
