#include "functions.h"
#include "../cpu/idt.h"

void main() {
    //clear_screen();
    //enable_cursor(1, 13);
    //kprint("usr $ ");
    init_idt(); //Initialises the IDT

    __asm__ __volatile__ ("int $10"); // CPU Panics here

    // Problem: CPU Panics when getting a interrupt

    /* Files:
     * int handeler:    cpu/isr.c   https://github.com/cheyao/OS/blob/master/cpu/isr.c
     *
     * init_idt:        cpu/idt.c   https://github.com/cheyao/OS/blob/master/cpu/idt.c
     *
     * asm code (isrs): cpu/idt.asm https://github.com/cheyao/OS/blob/master/cpu/idt.c
     */
}