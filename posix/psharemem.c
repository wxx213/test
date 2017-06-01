#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char *p = NULL;
    char buffer[20];
    char str[] = "write by wxx";
    int retval;
       
    memset(buffer,0,sizeof(buffer));
    fd = open("./wxx.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    if(fd < 0)
    {
        printf("open file error\n");
    }
    retval = write(fd,buffer,sizeof(buffer));
    if(retval < 0)
    {
        printf("write file error\n");
    }
    p = (char *)mmap(NULL,sizeof(buffer),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    if(p == MAP_FAILED)
    {
        printf("map file failed\n");
    }
    
    memcpy(p,str,sizeof(str));
    sleep(1);
    retval = msync(p,sizeof(str),MS_SYNC);
    if(retval != 0)
    {
        printf("msync file error\n");
    }
    sleep(1);
    munmap(p,sizeof(buffer));
    close(fd);
    return 0;
}
