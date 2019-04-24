#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *string_number_multiply(char *a, char *b)
{
    int len1, len2;
    char *c;
    int i, ii, j, jj, k, kk;
    char tmp, ai, bj;

    len1 = strlen(a);
    len2 = strlen(b);
    printf("len1 = %d, len2 = %d\n", len1, len2);
    c = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    if(!c) {
        printf("malloc error\n");
        return NULL;
    }
    memset((void *)c, '0', (len1 + len2 + 1) * sizeof(char));
    for(i = 0; i < len1; i ++) {
        for(j = 0; j < len2; j ++) {
            ii = len1 - i - 1;
            jj = len2 - j - 1;
            ai = a[ii] - '0';
            bj = b[jj] - '0';
            tmp = ai * bj;
            k = i + j;
            kk = len1 + len2 - k - 1;
            tmp = c[kk] - '0' + tmp;
            printf("tmp = %d, ai = %d, bj = %d\n", tmp, ai, bj);
            if(tmp >= 10) {
                printf("kk = %d, c[kk] = %c\n", kk, c[kk]);
                while(tmp >= 10) {
                    c[kk] = tmp % 10 + '0';
                    tmp = tmp / 10 + c[kk - 1] - '0';
                    c[kk - 1] = tmp + '0';
                    kk --;
                }
            }
            else {
                printf("kk = %d, c[kk] = %c\n", kk, c[kk]);
                c[kk] = tmp + '0';
            }
        }
    }
    c[len1 + len2] = '\0';
    return c;
}
