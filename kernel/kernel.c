#include "kernel/functions.h"
#include "cpu/idt.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"

void main() {
    //enable_cursor(1, 13);
    //clear_screen();

    //kprint("usr $ ");
    //init_idt();
    //__asm__ ("int $0");
    /*
    __asm__ __volatile__("sti");
    init_timer(60);
    init_keyboard();

    */
}

/*
 * Current memory map:
 *
 * 0x00000000 - 0x000004FF --  Unusable in real mode -- Don't use atm
 * 0x00001000 - 0x00005000 --  Paging descriptor table
 * 0x00005001 - 0x00007BFF --  Unused memory
 * 0x00007C00 - 0x00007D00 --  Boot sector -- usable after jumping to kernel
 * 0x00007E00 - 0x0007FFFF --  Kernel reserved -- currently used to
 */