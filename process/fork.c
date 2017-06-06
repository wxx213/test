#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int i;
	for(i=0;i<3;i++)
	{
		pid = fork();
		if(pid < 0)
		{
			printf("fork error\n");
			exit(1);
		}
		else if(0 == pid)
		{
			break;
		}
	}
	if(pid > 0)
	{
		printf("process main pid: %d\n",getpid());
		while(wait(NULL) != -1);
	}
	else if(0 == pid)
	{
		switch(i)
		{
			case 0:
				printf("process1 ppid: %d\n",getppid());
				break;
			case 1:
				printf("process2 ppid: %d\n",getppid());
				break;
			case 2:
				printf("process3 ppid: %d\n",getppid());
				break;
		}
		exit(0);
	}
	return 0;
}
