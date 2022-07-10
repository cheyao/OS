#include "isr.h"
#include "../kernel/functions.h"

void int_handler(u8int exception) {
    char* str = "0";    // Turns one digit ints to strings, enough for now
    *str += exception;
    kprint(str);// Prints the int
}
