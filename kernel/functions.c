#include "functions.h"
#include "../drivers/ports.h"

/* Declaration of private functions */
int print_char(char c, int offset, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
int max(int i, int j);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void kprint_at(const char *message, int col, int row) {
    /* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
    }

    while (*message != 0x00) {
        offset = print_char(*message, offset, WHITE_ON_BLACK);
        message++;
    }

    if (offset > MAX_COLS * MAX_ROWS * 2) {
        scroll();
    }
}

void kprint(char *message) {
    message++;

    kprint_at(message, -1, -1);
}


/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * Innermost print function for our kernel, directly accesses the video memory
 *
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */
int print_char(const char c, int offset, char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (c == '\n') {
        offset = max(offset, 160) * 160 + 160;
    } else {
        vidmem[offset++] = c;
        vidmem[offset++] = attr;
    }

    set_cursor_offset(offset);

    return offset;
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (int) (offset & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (int) ((offset >> 8) & 0xFF));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (char *) VIDEO_ADDRESS;

    for (i = 0; i < screen_size * 2; i = i) {
        screen[i++] = ' ';
        screen[i++] = WHITE_ON_BLACK;
    }

    set_cursor_offset(0x00);
}

void scroll() {
    volatile char* video_memory = (volatile char *) VIDEO_ADDRESS;
    volatile char* video_memory_80 = (volatile char *) VIDEO_ADDRESS + 160;

    while (video_memory < VIDEO_ADDRESS + MAX_COLS * MAX_ROWS * 2) {
        *video_memory = *video_memory_80;
        video_memory_80++;
        video_memory++;
    }

    volatile char* clear = (volatile char*) 0xB7F60;

    while (clear != (char*) VIDEO_ADDRESS) {
        *clear = 0;
        clear++;
    }

    set_cursor_offset(get_cursor_offset() - 160);
}

void enable_cursor(int cursor_start, int cursor_end) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int max(int i, int j) {
    int x = -1;
    while (i >= 0) {
        i -= j;
        x++;
    }
    return x;
}

int get_offset_row(int offset) { return offset / (2 * 80); }
int get_offset_col(int offset) { return (int) ((offset - (get_offset_row(offset)*2))/2); }


void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
}