#include "idt.h"

static idtr_t idtr;
__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

void idt_set_descriptor(u8int vector, void* isr, u8int flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (u32int)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (u32int)isr >> 16;
    descriptor->reserved       = 0;
}

extern void* isr_stub_table[];

void idt_init() {
    idtr.size   = (u16int) sizeof(idt_entry_t) - 1;
    idtr.offset = (u32int) &idt[0];

    for (u8int vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }

    __asm__ __volatile__ ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ __volatile__ ("sti"); // set the interrupt flag
}