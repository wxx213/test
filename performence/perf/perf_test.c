#include <stdio.h>
#include <stdlib.h>

void func1()
{
	unsigned long i,j;
	for(i=0;i++;i<10000000) {
		j++;
	}
}

void func2()
{
	unsigned long i,j;
	for(i=0;i++;i<100000) {
		j++;
	}
}
int main()
{
	while(1) {
		func1();
		func2();
	}
	return 0;
}
