#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUF_SIZE    32

int main()
{
    char map_buf[BUF_SIZE];
    char *p_buf;
    pid_t pid;
    int status;

    p_buf = (char *)mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(MAP_FAILED == p_buf) {
        printf("mmap error\n");
        return 1;
    }

    pid = fork();
    if(pid < 0) {
        printf("fork error\n");
        return 1;
    }
    else if(0 == pid) {
        memcpy(p_buf, "This is child process", strlen("This is child process"));
        sleep(2);
        exit(0);
    }
    else {
        waitpid(pid, &status, WUNTRACED | WCONTINUED);
        printf("%s\n", p_buf);
        munmap(p_buf, BUF_SIZE);
    }
    return 0;
}
