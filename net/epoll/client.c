#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>


void *working(void *arg)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        printf("子线程：%ld, error in create　socket\n",pthread_self());
        pthread_exit(NULL);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10000);
    inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        printf("子线程：%ld, error in connect socket\n",pthread_self());
        pthread_exit(NULL);
    }

    int cnt = 0;
    char buffer[1024];
    while (cnt<=100)
    {
        sprintf(buffer, "子线程：%ld, 当前消息计数器为cnt:%d\n",pthread_self(),cnt);
        write(fd, buffer, strlen(buffer) + 1);

        memset(buffer, 0, sizeof(buffer));
        int len = read(fd, buffer, sizeof(buffer));
        if(len>0){
            printf("子线程：%ld, 服务器消息：%s\n",pthread_self(), buffer);
        }
        else if(len == 0)
        {
            printf("子线程：%ld, 无消息，断开连接：%s\n",pthread_self(), buffer);
        }
        else{
            printf("子线程：%ld, error in read socket\n",pthread_self());
            pthread_exit(NULL);
        }
        sleep(1);
        cnt++;
    }

    close(fd);
}

int main()
{
    int n = 3;
    for(int i=0; i<n; i++)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, working, NULL);
        pthread_detach(tid);
    }
    pthread_exit(NULL);


    return 0;
}
