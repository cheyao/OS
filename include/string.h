#ifndef STRING_H
#define STRING_H

#include "types.h"

char * strtok(char *str, const char *delim);
bool strcmp(char i[], char j[]);
bool strcasecmp(char i[], char j[]);
int strlen(char s[]);
void int_to_ascii(int n, char str[]);
void reverse(char s[]);

#endif