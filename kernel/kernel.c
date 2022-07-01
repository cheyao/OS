#include "functions.h"
#include "../cpu/isr.h"

void main() {
    clear_screen();
    enable_cursor(1, 13);
    isr_install();

    kprint("usr $ ");
    kprint("brew install macOS\nUpdating brew...");
    __asm__ __volatile__ ("int $2");
}