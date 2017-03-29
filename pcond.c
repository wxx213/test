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
		sleep(5);
		/*operate x,y*/
		if(x > y){
			pthread_cond_signal(&cond);
		}
		printf("after cond\n");
		pthread_mutex_unlock(&mutex);
		printf("1 unlocked\n");	
	}
	return;
}
void thread2(void)
{
	while(1){
		pthread_mutex_lock(&mutex);
		printf("2 locked\n");
		while(x <= y){
			pthread_cond_wait(&cond,&mutex);
		}
		/*operate x,y*/
		printf("wake up\n");
		sleep(5);
		pthread_mutex_unlock(&mutex);
	}
	return;
}
int main()
{
	pthread_t pid1,pid2;
	int retval;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
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
	while(1){
		printf("input x,y\n");
		scanf("%d%d",&x,&y);
		printf("x=%d,y=%d\n",x,y);
		
	}
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	return 0;
}
