#include "functions.h"
#include "archive/drivers/ports.h"
#include "archive/drivers/timer.h"

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
    unsigned char *vid_mem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (c == '\n') {
        offset = max(offset, 160) * 160 + 160;
    } else {
        vid_mem[offset++] = c;
        vid_mem[offset++] = attr;
    }

    return offset;
}

/// Use the VGA ports to get the current cursor position
/// 1. Ask for high byte of the cursor offset (data 14)
/// 2. Ask for low byte (data 15)
int get_cursor_offset() {
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(u32int offset) {
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

    for (i = 0; i < screen_size * 2;) {
        screen[i++] = ' ';
        screen[i++] = WHITE_ON_BLACK;
    }

    set_cursor_offset(0x00);
}

void scroll() {
    volatile char* video_memory = (volatile char *) VIDEO_ADDRESS;
    volatile char* video_memory_80 = (volatile char *) VIDEO_ADDRESS + 160;

    while ((u32int) video_memory < VIDEO_ADDRESS + MAX_COLS * MAX_ROWS * 2) {
        *video_memory = *video_memory_80;
        if ((u32int) video_memory_80 % 2 == NULL) {
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

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

/* Deletes the item before the cursor on the screen */
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
    for (i = NULL; l[i] != NULL; i++) {}
    l[i] = letter;
    i++;
    l[i] = NULL;
}

char pop(char l[]) {
    int i;
    char tmp;
    for (i = NULL; l[i] != NULL; i++) {}
    if (i == NULL) return NULL;
    i--;
    tmp = l[i];
    l[i] = NULL;
    return tmp;
}

void * memset (void *dest, int val, int len) {
    unsigned char *d = dest;
    while (len-- > NULL) *d++ = val;
    return dest;
}

char * strtok(char *str, const char *delim) {
    register char *spanp;
    register int c, sc;
    char *tok;
    static char *last;


    if (str == NULL && (str = last) == NULL)
        return (NULL);

    /*
     * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
     */
    cont:
    c = *str++;
    for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
        if (c == sc)
            goto cont;
    }

    if (c == 0) {		/* no non-delimiter characters */
        last = NULL;
        return (NULL);
    }
    tok = str - 1;

    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    for (;;) {
        c = *str++;
        spanp = (char *)delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    str = NULL;
                else
                    str[-1] = 0;
                last = str;
                return (tok);
            }
        } while (sc != 0);
    }
}

bool strcmp(char i[], char j[]) {
    int p = 0;

    for (; i[p] != 0 && j[p] != 0; p++) if (i[p] != j[p]) return False

    return True
}

bool strcasecmp(char i[], char j[]) {
    int p = 0;
    char t, u;

    if ((i[p] == 0 && j[p] != 0) || (i[p] != 0 && j[p] == 0)) return False

    for (; i[p] != 0 && j[p] != 0; p++) {
        t = i[p];
        u = j[p];
        if ('A' <= i[p] && i[p] <= 'Z') {
            t = i[p] - ('A' - 'a');
        }
        if ('A' <= j[p] && j[p] <= 'Z') {
            u = i[p] - ('A' - 'a');
        }

        if (t != u) return False
    }

    return True
}
