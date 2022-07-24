#ifndef FUNCTIONS_H

#include "kernel/types.h"

#define FUNCTIONS_H
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
#define NULL 0

/* Public kernel API */
void clear_screen();
void kprint_at(const char *message, int col, int row);
void kprint(char *message);
void kdel();
void kdel_at(int row, int col);
void enable_cursor(int cursor_start, int cursor_end);
int get_cursor_offset();
void set_cursor_offset(u32int offset);
void scroll();
void * memset (void *dest, int val, int len);
void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void append(char list[], char letter);
char pop(char list[]);
char * strtok(char *str, const char *delim);
bool strcmp(char i[], char j[]);
bool strcasecmp(char i[], char j[]);

#define UNUSED(x) (void)(x)

#endif
