#include "idt.h"

static idt_t  idt[31];   // Defines 32 idts
static idtr_t idtr;      // Makes a idtr

void set_idt(int vector, u32int offset) {
    //vector -= 11; // Used gdb to debug, the idt[vector] always points to the idt that is 11 farther
    idt[vector].low         = low_16(offset);   // (u16int)(((offset) >> 16) & 0xFFFF)
    idt[vector].selector    = 0x08;             // Sector
    idt[vector].zero        = 0;                // Reserved
    idt[vector].type        = 0x8e;             // ISR = 0x8E
    idt[vector].high        = high_16(offset);  // (u16int)((offset) & 0xFFFF)
}

void init_idt() {
    // Wrote these functions by hand to avoid errors
    set_idt(0 , (u32int) isr_0 );
    set_idt(1 , (u32int) isr_1 );
    set_idt(2 , (u32int) isr_2 );
    set_idt(3 , (u32int) isr_3 );
    set_idt(4 , (u32int) isr_4 );
    set_idt(5 , (u32int) isr_5 );
    set_idt(6 , (u32int) isr_6 );
    set_idt(7 , (u32int) isr_7 );
    set_idt(8 , (u32int) isr_8 );
    set_idt(9 , (u32int) isr_9 );
    set_idt(10, (u32int) isr_10);
    set_idt(11, (u32int) isr_11);
    set_idt(12, (u32int) isr_12);
    set_idt(13, (u32int) isr_13);
    set_idt(14, (u32int) isr_14);
    set_idt(15, (u32int) isr_15);
    set_idt(16, (u32int) isr_16);
    set_idt(17, (u32int) isr_17);
    set_idt(18, (u32int) isr_18);
    set_idt(19, (u32int) isr_19);
    set_idt(20, (u32int) isr_20);
    set_idt(21, (u32int) isr_21);
    set_idt(22, (u32int) isr_22);
    set_idt(23, (u32int) isr_23);
    set_idt(24, (u32int) isr_24);
    set_idt(25, (u32int) isr_25);
    set_idt(26, (u32int) isr_26);
    set_idt(27, (u32int) isr_27);
    set_idt(28, (u32int) isr_28);
    set_idt(29, (u32int) isr_29);
    set_idt(30, (u32int) isr_30);
    set_idt(31, (u32int) isr_31);

    idtr.base  = (u32int) &idt[0];              // Assigns the position of idt[0] to idtr.base
    idtr.limit = sizeof(idt_t) * 32 - 1;        // According to the intel IA-32 manuel, all idts are 8 bytes big

    __asm__ __volatile__ ("lidt %0" :: "m" (idtr)); // Loads the IDTR
}
