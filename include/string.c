#include "string.h"

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

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

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

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
