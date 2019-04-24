#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "array.h"

int main()
{
    char a[] = "122345";
    char b[] = "345555";
    printf("%s\n", string_number_multiply(a, b));
    return 0;
}
