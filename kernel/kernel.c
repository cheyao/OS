#include "functions.h"
#include "../cpu/idt.h"

void main() {
    clear_screen();
    enable_cursor(1, 13);
    idt_init();

    //kprint("usr $ ");
    //kprint("brew install macOS\nUpdating brew...");
}