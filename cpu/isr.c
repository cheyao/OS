//
// Created by cyao on 02.07.2022.
//

#include "isr.h"
#include "../kernel/functions.h"


void exception_handler(u8int exception) {
    char* i = "0";
    kprint("Recieved interupt: ");
    *i += exception;
    kprint(i);
}
