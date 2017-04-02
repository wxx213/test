#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	pid_t pid;
	int fd;
	char buffer[20];
	int retval;
	/*int fd1[2];
	char buffer[20];
	retval = pipe(fd1);
	if(retval < 0){
		printf("pipe1 error\n");
		exit(0);
	}*/
	retval = mkfifo("/home/wxx213/test/fifo",S_IFIFO | 0666);
	if(retval < 0){
		printf("mkfifo error:%s\n",strerror(errno));
		exit(0);
	}
	pid = fork();
	if(pid < 0){
		printf("fork error\n");
		exit(0);
	} 
	else if(0 == pid){
		/*close(fd1[1]);
		read(fd1[0],buffer,20);
		close(fd1[0]);
		printf("\n");
		puts(buffer);*/
		/*fd = open("/home/wxx213/test/fifo",O_RDWR,0);
		if(fd < 0){
			printf("open error:%s\n",strerror(errno));
			exit(0);
		}
		retval = read(fd,buffer,20);
		if(retval < 0){
			printf("read error:%s\n",strerror(errno));
			exit(0);
		}
		close(fd);
		//printf("\n");
		puts(buffer);*/
		exit(0);
	}
	else{
		/*close(fd1[0]);
		sprintf(buffer,"this is parent");
		write(fd1[1],buffer,sizeof(buffer));
		close(fd1[1]);*/
		fd = open("/home/wxx213/test/fifo",O_RDWR,0);
		if(fd < 0){
			printf("open error:%s\n",strerror(errno));
			exit(0);
		}
		sprintf(buffer,"this is parent");
		retval = write(fd,buffer,sizeof(buffer));
		if(retval < 0){
			printf("write error:%s\n",strerror(errno));
			exit(0);
		}
		close(fd);
		wait(0);
		//unlink("/home/wxx213/test/fifo");
		exit(0);
	}
	return 0;
}
