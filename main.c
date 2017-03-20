//#include <stdio.h>

int time = 12;
int result;
extern int sum(int a,int b);
int main()

{
	int i;
	for(i=0;i<6;i++)
	{
		result = sum(i,time);
		//printf("%d\n",result);
	}
	return 0;
}

