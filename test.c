#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char a[10];
    int b[10];

    printf("&a[1] = %lu\n",&a[1]);
    printf("&a[2] = %lu\n",&a[2]);
    printf("a = %lu\n", a);
    printf("a+1 = %lu\n", a+1);
    printf("&b[1] = %lu\n",&b[1]);
    printf("&b[2] = %lu\n",&b[2]);
    printf("b = %lu\n", b);
    printf("b+1 = %lu\n", b+1);
	return 0;	
}
