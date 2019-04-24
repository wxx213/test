#include <stdio.h>
#include <stdlib.h>

#include "string.h"

int string_atoi(char *str)
{
    char *p = str;
    int i = 0;

    while(*p != '\0') {
        //printf("%c\n", *p);
        i = i * 10 + *p - '0';
        p ++;
    }
    return i;
}
