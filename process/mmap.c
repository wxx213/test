#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int fd,zero;
	int retval;
	int *ptr;
	sem_t *sem;
	int i,count = 20;
	
	fd = open("./wxx.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    if(fd < 0)
    {
        printf("open file error\n");
        exit(0);
    }
    zero = 0;
    retval = write(fd,&zero,sizeof(int));
    if(-1 == retval)
    {
    	printf("write file error\n");
    	exit(0);
    }
    ptr = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(MAP_FAILED == ptr)
    {
    	printf("mmap error\n");
    	exit(0);
    }
    close(fd);
    sem = sem_open("/wxx",O_RDWR|O_CREAT,0644,1);
	if(SEM_FAILED == sem)
	{
		printf("sem_open error\n");
		exit(0);
	}
	sem_unlink("/wxx");
    pid = fork();
    if(pid < 0)
    {
    	printf("fork error\n");
    	exit(0);
    }
    else if(0 == pid)
    {
    	for(i=0;i<count;i++)
    	{
    		sleep(1);
			sem_wait(sem);
			(*ptr) ++;
			printf("child: %d\n",(*ptr));
			sem_post(sem);
		}
    	
    }
    else
    {
    	for(i=0;i<count;i++)
    	{
    		sleep(1);
			sem_wait(sem);
			(*ptr) ++;
			printf("parent: %d\n",(*ptr));
			sem_post(sem);
		}
		
    }
	return 0;
}
