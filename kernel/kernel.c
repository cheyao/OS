#include "kernel/functions.h"
#include "cpu/idt.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"

int main() {
    clear_screen();
    enable_cursor(1, 13);
    init_idt();
    __asm__ __volatile__("sti");
    init_timer(60);
    init_keyboard();

    kprint("                                                                           00:00");
    kprint("usr $ ");

    return 1;
}
