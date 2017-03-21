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
	char buffer_r[20];
	int retval,i;
	unsigned int prio;
	printf("thread1: %d\n",mqd);
	retval = mq_send(mqd,buffer,sizeof(buffer),1);
	if(retval == -1){
		printf("mq_send eror\n");
		return;
	}
	/*do{
		retval = mq_receive(mqd,buffer_r,20,&prio);
		if(retval == -1){
			printf("thread1: mq_receive error\n");
			return;
		}
	}while(prio != 2);
	printf("thread1:");
	for(i=0;i<20;i++){
		if(*(buffer_r + i) == '\0')
			break;
		printf("%c",*(buffer_r + i));
	}
	printf("\n");*/
	return;
}
void thread2(void)
{
	unsigned int prio;
	char buffer[20];
	char buffer_s[] = "thread2 received";
	int i,retval;
	printf("thread2: %d\n",mqd);
	//do{
		retval = mq_receive(mqd,buffer,20,&prio);
		if(retval == -1){
			printf("thread2: mq_reveive error: %s\n",strerror(errno));
			return;
		}
	//}while(prio != 1);
	printf("thread2:");
	for(i=0;i<20;i++){
		if(*(buffer + i) == '\0')
			break;
		printf("%c",*(buffer + i));
	}
	printf("\n");
	/*retval = mq_send(mqd,buffer_s,sizeof(buffer_s),2);
	if(retval == -1){
		printf("thread2: mq_send error\n");
		return ;
	}*/
	return;
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
		return 0;
	}
	printf("main: %d\n",mqd);
	
	retval = pthread_create(&pid1,NULL,(void *)thread1,NULL);
	if(retval != 0){
		printf("creatw thread1 error\n");
		return 0;
	}

	retval = pthread_create(&pid2,NULL,(void *)thread2,NULL);
	if(retval != 0){
		printf("creatw thread2 error\n");
		return 0;
	}
	pthread_join(pid1,(void **)buffer);
	pthread_join(pid1,(void **)buffer);
	mq_close(mqd);
	return 0;
}
