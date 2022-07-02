//
// Created by cyao on 01.07.2022.
// Fuck all tutorials im going to write this by my self
//

#ifndef OS_IDT_H
#define OS_IDT_H

#include "../kernel/types.h"

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
    u16int      isr_low;      // The lower 16 bits of the ISR's address
    u16int      kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
    u8int       reserved;     // Set to zero
    u8int       attributes;   // Type and attributes; see the IDT page 0x8e
    u16int      isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    u16int 	    size;
    u32int 	    offset;
} __attribute__((packed)) idtr_t;

void idt_set_descriptor(u8int vector, void* isr, u8int flags);
void idt_init(void);


#endif
