#include "cpu/idt.h"
#include "cpu/isr.h"
#include "kernel/bash.h"
#include "kernel/functions.h"
#include "drivers/keyboard.h"
#include "drivers/ports.h"
#include "stdmem.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];
static int shift = 0;
#define SC_MAX 57

char uppercase(char letter);

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                          "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                          "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                          "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                          "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                          "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
                          '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                          'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                          'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                          'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(u8int int_no) {
    u8int scancode = inb(0x60);

    if (scancode == BACKSPACE) {
        switch (key_buffer[0]) {
            case 0:
                break;
            default:
                kdel();
                pop(key_buffer);
                break;
        }
    }
    else if (scancode == ENTER) {
        kprint("\n");
        run(key_buffer);
        memset(key_buffer, 0, sizeof key_buffer);
    }
    else if (scancode == 0x2A || scancode == 0x36) shift = 1;
    else if (scancode == 0x2A + 0x80 || scancode == 0x36 + 0x80) shift = 0;
    else if (scancode == 0x3A) shift ^= 0;
    else {
        char letter = sc_ascii[scancode];

        if (scancode > 0x80 || letter == '?') return;
        if (!shift && 'A' <= letter && letter <= 'Z') letter += 'a' - 'A';
        if (shift) letter = uppercase(letter);

        char i[2] = {letter, 0};

        kprint(i);
        append(key_buffer, letter);
    }
    UNUSED(int_no);
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}

char uppercase(char letter) {
    switch (letter) {
        case ';':
            letter = ':';
            break;
        case '\'':
            letter = '"';
            break;
        case ']':
            letter = '}';
            break;
        case '[':
            letter = '{';
            break;
        case '\\':
            letter = '|';
            break;
        case '/':
            letter = '?';
            break;
        case '.':
            letter = '>';
            break;
        case ',':
            letter = '<';
            break;
        case '`':
            letter = '~';
            break;
        case '1':
            letter = '!';
            break;
        case '2':
            letter = '@';
            break;
        case '3':
            letter = '#';
            break;
        case '4':
            letter = '$';
            break;
        case '5':
            letter = '%';
            break;
        case '6':
            letter = '^';
            break;
        case '7':
            letter = '&';
            break;
        case '8':
            letter = '*';
            break;
        case '9':
            letter = '(';
            break;
        case '0':
            letter = ')';
            break;
        case '-':
            letter = '_';
            break;
        case '=':
            letter = '+';
            break;
        default:
            break;
    }
    return letter;
}
