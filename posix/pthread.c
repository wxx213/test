#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void thread1(void)
{
	printf("thread1 pid: %d\n",getpid());
	printf("thread1 tid: %d\n",pthread_self());
	pthread_exit(NULL);
}
void thread2(void)
{
	printf("thread2 pid: %d\n",getpid());
	printf("thread1 tid: %d\n",pthread_self());
	pthread_exit(NULL);
}
int main()
{
	pthread_t pid1,pid2;
	int retval;
	
	retval = pthread_create(&pid1,NULL,(void *)thread1,NULL);
	if(retval != 0)
	{
		printf("error1\n");
		return 0;
	}
	retval = pthread_create(&pid2,NULL,(void *)thread2,NULL);
	if(retval != 0)
	{
		printf("error2\n");
		return 0;
	}
	printf("main pid: %d\n",getpid());
	printf("main pid1: %d\n",pid1);
	printf("main pid2: %d\n",pid2);
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	return 0;
}
