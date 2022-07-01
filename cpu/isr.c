#include "isr.h"
#include "idt.h"
#include "../kernel/functions.h"

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
    set_idt_gate(0, (u32int)isr0);
    set_idt_gate(1, (u32int)isr1);
    set_idt_gate(2, (u32int)isr2);
    set_idt_gate(3, (u32int)isr3);
    set_idt_gate(4, (u32int)isr4);
    set_idt_gate(5, (u32int)isr5);
    set_idt_gate(6, (u32int)isr6);
    set_idt_gate(7, (u32int)isr7);
    set_idt_gate(8, (u32int)isr8);
    set_idt_gate(9, (u32int)isr9);
    set_idt_gate(10, (u32int)isr10);
    set_idt_gate(11, (u32int)isr11);
    set_idt_gate(12, (u32int)isr12);
    set_idt_gate(13, (u32int)isr13);
    set_idt_gate(14, (u32int)isr14);
    set_idt_gate(15, (u32int)isr15);
    set_idt_gate(16, (u32int)isr16);
    set_idt_gate(17, (u32int)isr17);
    set_idt_gate(18, (u32int)isr18);
    set_idt_gate(19, (u32int)isr19);
    set_idt_gate(20, (u32int)isr20);
    set_idt_gate(21, (u32int)isr21);
    set_idt_gate(22, (u32int)isr22);
    set_idt_gate(23, (u32int)isr23);
    set_idt_gate(24, (u32int)isr24);
    set_idt_gate(25, (u32int)isr25);
    set_idt_gate(26, (u32int)isr26);
    set_idt_gate(27, (u32int)isr27);
    set_idt_gate(28, (u32int)isr28);
    set_idt_gate(29, (u32int)isr29);
    set_idt_gate(30, (u32int)isr30);
    set_idt_gate(31, (u32int)isr31);

    set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",

        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",

        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",

        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
};

void isr_handler(registers_t r) {
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
}