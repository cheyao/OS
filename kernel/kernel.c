#include "../drivers/ports.h"
#include "functions.h"
#include "kernel.h"

void main() {
    clear_sc();

    // print_at("H", 0, 0);
    volatile char* message = 'H';
    volatile char* sc = 0xb8001;
    *sc = 'H';
}