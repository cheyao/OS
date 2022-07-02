#ifndef FUNCTIONS_H

#include <stddef.h>
#include "types.h"

#define FUNCTIONS_H
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void clear_screen();
void kprint_at(const char *message, int col, int row);
void kprint(char *message);
void enable_cursor(int cursor_start, int cursor_end);
int get_cursor_offset();
void set_cursor_offset(int offset);
void scroll();
void * memset (void *dest, int val, size_t len);
void * memmove (void *dest, const void *src, size_t len);
void * memcpy (void *dest, const void *src, size_t len);
int memcmp (const void *str1, const void *str2, size_t count);
void kprint_hex(u8int hex);
void int_to_ascii(int n, char str[]);
char * itoa(int value, int digits);
#endif