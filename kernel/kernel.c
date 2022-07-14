#include "functions.h"
#include "../cpu/idt.h"

void main() {
    clear_screen();
    enable_cursor(1, 13);
    init_idt(); //Initialises the IDT, all good

    kprint("usr $ ");
    __asm__ __volatile__ ("int $0"); // CPU Panics here

    /* Files:
     * gdt:             boot/gdt.asm https://github.com/cheyao/OS/blob/master/boot/gdt.asm
     *
     * int handeler:    cpu/isr.c    https://github.com/cheyao/OS/blob/master/cpu/isr.c
     *
     * init_idt:        cpu/idt.c    https://github.com/cheyao/OS/blob/master/cpu/idt.c
     *
     * asm code (isrs): cpu/idt.asm  https://github.com/cheyao/OS/blob/master/cpu/idt.asm
     */
}
