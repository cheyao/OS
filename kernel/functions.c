#include "kernel/functions.h"
#include "drivers/ports.h"
#include "drivers/timer.h"

/* Declaration of private functions */
int print_char(char c, int offset, char attr);
int get_offset(int col, int row);
int max(int i, int j);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void kprint_at(char *message, int col, int row) {
    /* Set cursor if col/row are negative */
    int offset;

    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();


    while (*message != 0x00) {
        offset = print_char(*message, offset, WHITE_ON_BLACK);
        message++;
    }

    if (col < 0 || row < 0) {
        set_cursor_offset(offset);

        if (offset > MAX_COLS * MAX_ROWS * 2) {
            scroll();
        }
    }
}

// Prints to the place of the cursor
void kprint(char *message) {
    kprint_at(message, -1, -1);
}

int print_char(const char c, int offset, char attr) {
    if (c == '\n') {
        offset = max(offset, 160) * 160 + 160;
    } else {
        *((char *) VIDEO_ADDRESS + offset) = c;
        *((char *) VIDEO_ADDRESS + offset + 1) = attr;
    }

    return offset + 2;
}

int get_cursor_offset() {
    outb(0x3D4, 0x0F);

    u16int pos = inb(0x3D5);

    outb(0x3D4, 0x0E);

    pos |= ((u16int) inb(0x3D5)) << 8;

    return pos * 2;
}

void set_cursor_offset(u32int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (u8int) (offset & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (u8int) ((offset >> 8) & 0xFF));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (char *) VIDEO_ADDRESS;

    for (i = 0; i < screen_size * 2;) {
        screen[i++] = ' ';
        screen[i++] = WHITE_ON_BLACK;
    }

    set_cursor_offset(0);
}

void scroll() {
    volatile char* video_memory = (volatile char *) VIDEO_ADDRESS;
    volatile char* video_memory_80 = (volatile char *) VIDEO_ADDRESS + 160;

    while ((u64int) video_memory < VIDEO_ADDRESS + MAX_COLS * MAX_ROWS * 2) {
        *video_memory = *video_memory_80;
        if ((u64int) video_memory_80 % 2 == NULL) {
            *video_memory_80 = ' ';
        }
        video_memory_80++;
        video_memory++;
    }

    volatile char* clear = (volatile char*) 0xB7F60;

    while (clear != (char*) VIDEO_ADDRESS) {
        *clear = 0;
        clear++;
    }

    set_cursor_offset(get_cursor_offset() - 160);

    print_time(75, 0);
}

void enable_cursor(int cursor_start, int cursor_end) {
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);

    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
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

void kdel() {
    kdel_at(-1, -1);
}


void kdel_at(int row, int col) {
    /* Set cursor if col/row are negative */
    u32int offset;

    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    *((char*) VIDEO_ADDRESS + offset - 2) = ' ';

    if (col < 0 || row < 0) {
        set_cursor_offset(offset - 2);
    }
}

void append(char l[], char letter) {
    int i;
    for (i = NULL; l[i] != NULL; i++);
    l[i] = letter;
    i++;
    l[i] = NULL;
}

char pop(char l[]) {
    int i;
    char tmp;
    for (i = NULL; l[i] != NULL; i++);

    if (i == NULL) return NULL;

    i--;
    tmp = l[i];
    l[i] = NULL;
    return tmp;
}
