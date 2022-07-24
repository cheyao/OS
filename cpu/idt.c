#include "cpu/idt.h"
#include "drivers/ports.h"

extern void flush_idt(u32int idt);

void set_idt(int vector, u32int offset) {
    idt[vector].low         = low_16(offset);   // (u16int)(((offset) >> 16) & 0xFFFF)
    idt[vector].selector    = 0x08;             // Sector
    idt[vector].zero        = 0;                // Reserved
    idt[vector].type        = 0x8e;             // ISR = 0x8E
    idt[vector].high        = high_16(offset);  // (u16int)((offset) & 0xFFFF)
}

void init_idt() {
    // Remap the PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Wrote these functions by hand to avoid errors
    set_idt(0 , (u64int) isr_0 );
    set_idt(1 , (u64int) isr_1 );
    set_idt(2 , (u64int) isr_2 );
    set_idt(3 , (u64int) isr_3 );
    set_idt(4 , (u64int) isr_4 );
    set_idt(5 , (u64int) isr_5 );
    set_idt(6 , (u64int) isr_6 );
    set_idt(7 , (u64int) isr_7 );
    set_idt(8 , (u64int) isr_8 );
    set_idt(9 , (u64int) isr_9 );
    set_idt(10, (u64int) isr_10);
    set_idt(11, (u64int) isr_11);
    set_idt(12, (u64int) isr_12);
    set_idt(13, (u64int) isr_13);
    set_idt(14, (u64int) isr_14);
    set_idt(15, (u64int) isr_15);
    set_idt(16, (u64int) isr_16);
    set_idt(17, (u64int) isr_17);
    set_idt(18, (u64int) isr_18);
    set_idt(19, (u64int) isr_19);
    set_idt(20, (u64int) isr_20);
    set_idt(21, (u64int) isr_21);
    set_idt(22, (u64int) isr_22);
    set_idt(23, (u64int) isr_23);
    set_idt(24, (u64int) isr_24);
    set_idt(25, (u64int) isr_25);
    set_idt(26, (u64int) isr_26);
    set_idt(27, (u64int) isr_27);
    set_idt(28, (u64int) isr_28);
    set_idt(29, (u64int) isr_29);
    set_idt(30, (u64int) isr_30);
    set_idt(31, (u64int) isr_31);

    // Install the IRQs
    set_idt(32, (u64int) irq_0 );
    set_idt(33, (u64int) irq_1 );
    set_idt(34, (u64int) irq_2 );
    set_idt(35, (u64int) irq_3 );
    set_idt(36, (u64int) irq_4 );
    set_idt(37, (u64int) irq_5 );
    set_idt(38, (u64int) irq_6 );
    set_idt(39, (u64int) irq_7 );
    set_idt(40, (u64int) irq_8 );
    set_idt(41, (u64int) irq_9 );
    set_idt(42, (u64int) irq_10);
    set_idt(43, (u64int) irq_11);
    set_idt(44, (u64int) irq_12);
    set_idt(45, (u64int) irq_13);
    set_idt(46, (u64int) irq_14);
    set_idt(47, (u64int) irq_15);

    idtr.base  = (u64int) &idt[0];              // Assigns the position of idt[0] to idtr.base
    idtr.limit = sizeof(idt_t) * 256 - 1;        // According to the intel IA-32 manuel, all idts are 8 bytes big

    flush_idt((u64int) &idtr);
}

