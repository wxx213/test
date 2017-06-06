#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int x = 0,y = 0;

void thread1(void)
{
	while(1){
		pthread_mutex_lock(&mutex);
		sleep(2);
		/*operate x,y*/
		if(x > y){
			pthread_cond_signal(&cond);
		}
		pthread_mutex_unlock(&mutex);
	}
	return;
}
void thread2(void)
{
	while(1){
		pthread_mutex_lock(&mutex);
		while(x <= y){
			pthread_cond_wait(&cond,&mutex);
		}
		/*operate x,y*/
		printf("wake up\n");
		sleep(2);
		pthread_mutex_unlock(&mutex);
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
