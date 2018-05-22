#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int event = 0;

void thread1(void)
{
	while(1){
		sleep(1);
		pthread_mutex_lock(&mutex);
		/* process shared resources */
		event = 1;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		pthread_exit(0);
	}
	return;
}
void thread2(void)
{
	while(1){
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		/* process shared resource */
		if(1 == event) {
			printf("received event from thread1\n");
		}
		else {
			printf("received other event from thread1");
		}
		pthread_mutex_unlock(&mutex);
		pthread_exit(0);
	}
	return;
}
int main()
{
	pthread_t tid1,tid2;
	int retval;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	retval = pthread_create(&tid1,NULL,(void *)thread1,NULL);
	if(retval != 0)
	{
		printf("error1\n");
		return 0;
	}
	retval = pthread_create(&tid2,NULL,(void *)thread2,NULL);
	if(retval != 0)
	{
		printf("error2\n");
		return 0;
	}
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
