#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd,retval,i;
	char buffer[] = "Created by wxx!";
	char buffer_r[20];
	fd = open("./wxx.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	if(fd < 0){
		printf("open error\n");
		return 0;
	}

	retval = write(fd,buffer,strlen(buffer));
	if(retval < 0){
		printf("write error\n");
		close(fd);
		return 0;
	}
	retval = lseek(fd,0,SEEK_SET);
	if(retval < 0){
		printf("lseek error\n");
		close(fd);
		return 0;
	}
	retval = read(fd,buffer_r,20);
	if(retval < 0){
		printf("read error\n");
		close(fd);
		return 0;
	}
	for(i=0;i<20;i++){
		if(*(buffer_r + i) == '\0')
			break;
		printf("%c",*(buffer_r + i));
	}
	printf("\n");

	close(fd);
	return 0;
}
