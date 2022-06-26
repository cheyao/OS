#include "functions.h"
#include "../drivers/ports.h"

/* Declaration of private functions */
void kprint(char* message, int offset);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// Prints at ___
void print_at(char* message, int row, int col) {
    kprint(message, (row * 80 + col) * 2);
}

// Prints at cursor position
void print(char* message) {
    kprint(message, get_cursor_offset());
}

// Real print function
void kprint(char* message, int offset) {
    // Stores sc position (0xb8000)
    volatile char* sc = (volatile char*) VIDEO_ADDRESS;

    // adds the offset to sc
    sc += offset;

    // While the char isnt 0x00, prints the char
    while (*message != 0) {
        *sc = *message;
        sc += 2;
        message++;
    }

    // Gets the offset and moves it one more letter
    offset = sc - VIDEO_ADDRESS + 2;
    // Sets the cursor position
    set_cursor_offset(offset);
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8; // High byte
    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA); // Low byte
    return offset * 2; // Position * size of character cell
}

void set_cursor_offset(int offset) {
    offset /= 2;
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void enable_cursor(int cursor_start, int cursor_end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}


void clear_sc() {
    volatile char* screen;
    int screen_size = MAX_COLS * MAX_ROWS;

    for (screen = (volatile char *) VIDEO_ADDRESS; (int) screen < VIDEO_ADDRESS + screen_size; screen ++) {
        *screen = ' ';
        screen ++;
        *screen = WHITE_ON_BLACK;
    }

    set_cursor_offset(0x00);
}


int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }