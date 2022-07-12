#include "functions.h"
#include "../cpu/idt.h"

void main() {
    clear_screen();
    enable_cursor(1, 13);
    init_idt(); //Initialises the IDT

    kprint("usr $ ");
    __asm__ __volatile__ ("int $1"); // CPU Panics here

    /* Files:
     * int handeler:    cpu/isr.c   https://github.com/cheyao/OS/blob/master/cpu/isr.c
     *
     * init_idt:        cpu/idt.c   https://github.com/cheyao/OS/blob/master/cpu/idt.c
     *
     * asm code (isrs): cpu/idt.asm https://github.com/cheyao/OS/blob/master/cpu/idt.c
     */
}
