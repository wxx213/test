#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>           
#include <sys/stat.h>      
#include <mqueue.h>
#include <errno.h>
#include <string.h>

mqd_t mqd;

void thread1(void)
{
	char buffer[] = "this is thread1";
	char buffer2[20];
	int retval,i;
	unsigned int prio;
	printf("thread1: %d\n",mqd);
	retval = mq_send(mqd,buffer,sizeof(buffer),1);
	if(retval == -1){
		printf("mq_send eror\n");
		pthread_exit(NULL);
	}

	prio = 0;
	while(prio != 2)
	{
		retval = mq_receive(mqd,buffer2,20,&prio);
		if(retval == -1){
			printf("thread2: mq_reveive error: %s\n",strerror(errno));
			pthread_exit(NULL);
		}
	}

	printf("thread1 received:");
	for(i=0;i<20;i++){
		if(*(buffer2 + i) == '\0')
			break;
		printf("%c",*(buffer2 + i));
	}
	printf("\n");
	pthread_exit(NULL);
}
void thread2(void)
{
	unsigned int prio;
	char buffer[20];
	char buffer2[] = "this is thread2";
	int i,retval;
	printf("thread2: %d\n",mqd);

	prio = 0;
	while(prio != 1)
	{	
		retval = mq_receive(mqd,buffer,20,&prio);
		if(retval == -1){
			printf("thread2: mq_reveive error: %s\n",strerror(errno));
			pthread_exit(NULL);
		}
	}
	printf("thread2 received:");
	for(i=0;i<20;i++){
		if(*(buffer + i) == '\0')
			break;
		printf("%c",*(buffer + i));
	}
	printf("\n");

	retval = mq_send(mqd,buffer2,sizeof(buffer2),2);
	if(retval == -1){
		printf("mq_send2 error: %s\n",strerror(errno));
		pthread_exit(NULL);
	}
	
	pthread_exit(NULL);
}
int main()
{
	int retval;
	pthread_t pid1,pid2;
	char *buffer[10];
	
	mode_t mod;
	struct mq_attr attr;
	
	attr.mq_maxmsg = 10;  
    attr.mq_msgsize = 20; 
	mqd = mq_open("/wxx",O_RDWR|O_CREAT,0644, &attr);
	if(mqd < 0){
		printf("mq_open error\n");
		exit(0);
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
	mq_close(mqd);
	mq_unlink("/wxx");
	exit(0);
}
