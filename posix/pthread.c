#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void *thread1(void *x)
{
	int local = 2;

	printf("thread1 pid: %d\n",getpid());
	printf("thread1 tid: %lu\n",pthread_self());
	printf("thread1 local: %d\n", local);
	pthread_exit(NULL);
	return NULL;
}
void *thread2(void *x)
{
	int local = 3;

	printf("thread2 pid: %d\n",getpid());
	printf("thread2 tid: %lu\n",pthread_self());
	printf("thread2 local: %d\n", local);
	pthread_exit(NULL);
	return NULL;
}
int main()
{
	pthread_t tid1,tid2;
	int retval;
	int local = 1;
	
	retval = pthread_create(&tid1,NULL,&thread1,NULL);
	if(retval != 0)
	{
		printf("error1\n");
		return 0;
	}
	retval = pthread_create(&tid2,NULL,&thread2,NULL);
	if(retval != 0)
	{
		printf("error2\n");
		return 0;
	}
	printf("main pid: %d\n",getpid());
	printf("main tid1: %lu\n",tid1);
	printf("main tid2: %lu\n",tid2);
	printf("main local: %d\n", local);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
