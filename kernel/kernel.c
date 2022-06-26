#include "../drivers/ports.h"
#include "functions.h"
#include "kernel.h"

void main() {
    clear_sc();
    enable_cursor(1, 13);

    print("Hello, world!"); // Prints very well
    print("Never gonna give you up"); // Dosn't print anything and moves the cursor one letter before?????????????
}