#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <semaphore.h>

sem_t *sem;
int ga;

void thread1(void)
{
	sem_wait(sem);
	ga = 1;
	printf("thread1: ga = 1\n");
	sem_post(sem);
	pthread_exit(NULL);
}
void thread2(void)
{
	sem_wait(sem);
	ga = 2;
	printf("thread2: ga = 2\n");
	sleep(10);
	sem_post(sem);
	pthread_exit(NULL);
}
int main()
{
    int retval;
	pthread_t pid1,pid2;
	
	sem = sem_open("/wxx",O_RDWR|O_CREAT,0644,1);
	if(SEM_FAILED == sem)
	{
		printf("sem_open error\n");
	}
	
	retval = pthread_create(&pid1,NULL,(void *)thread1,NULL);
	if(retval != 0){
		printf("creatw thread1 error\n");
		exit(0);
	}

	retval = pthread_create(&pid2,NULL,(void *)thread2,NULL);
	if(retval != 0){
		printf("creatw thread2 error\n");
		exit(0);
	}
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	exit(0);
}
