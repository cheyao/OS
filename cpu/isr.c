#include "cpu/isr.h"
#include "kernel/functions.h"
#include "drivers/ports.h"
#include "string.h"

isr_t interrupt_handlers[256];

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

void int_handler(u8int int_no, u8int err_code) {
    kprint("Int: ");// Prints the int
    kprint(exception_messages[int_no]);
    kprint("\n");

    char j[5];
    kprint("Err code: ");
    int_to_ascii(err_code, j);
    kprint(j);
}

void register_interrupt_handler(u8int n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(u8int int_no, u8int err_code) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (int_no >= 40) outb(0xA0, 0x20); /* slave */
    outb(0x20, 0x20); /* master */

    if (interrupt_handlers[int_no] != 0) {
        isr_t handler = interrupt_handlers[int_no];
        handler(int_no);
    }

    UNUSED(err_code);
}
