#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sa_thread_ext_handler(int sig)
{
	if(SIGUSR1 == sig) {
		printf("SIGUSR1 received, exitting...\n");
		pthread_exit(0);
	}
}
void *thread1(void *arg)
{
	struct sigaction act;

	printf("thread1 enter\n");
	memset(&act, 0, sizeof(act));
	act.sa_handler = sa_thread_ext_handler;
	sigemptyset(&act.sa_mask);
	act.sa_restorer = NULL;
	act.sa_flags = 0;
	/* On some architectures a union is involved: do not assign to both sa_handler and sa_sigaction. */
	//act.sa_sigaction = NULL;
	sigaction(SIGUSR1, &act, NULL);

	while(1);
}
int main(void)
{
	pthread_t tid;
	int ret;

	ret = pthread_create(&tid, NULL, thread1, NULL);
	if(ret != 0) {
		printf("pthread_create error\n");
		return 1;
	}
	sleep(2);
	pthread_kill(tid, SIGUSR1);
	pthread_join(tid, NULL);
	return 0;	
}
