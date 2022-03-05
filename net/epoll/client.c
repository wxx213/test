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
    int port = *((int *)(arg));
    addr.sin_port = htons(port);
    inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        printf("子线程：%ld, error in connect socket\n",pthread_self());
        pthread_exit(NULL);
    }

    int cnt = 0;
    char buffer[1024];
    while (cnt<1)
    {
        sprintf(buffer, "子线程：%ld, 当前消息计数器为cnt:%d,端口port:%d\n",pthread_self(),cnt,port);
        write(fd, buffer, strlen(buffer) + 1);

        memset(buffer, 0, sizeof(buffer));
        int len = read(fd, buffer, sizeof(buffer));
        if(len>0){
            printf("子线程：%ld, 来自服务器消息：%s\n",pthread_self(), buffer);
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
    int n = 1;
    for(int i=0; i<n; i++)
    {
        pthread_t tid1, tid2;
        int port1 = 9001, port2 = 9002;
        pthread_create(&tid1, NULL, working, &port1);
        pthread_detach(tid1);

        pthread_create(&tid2, NULL, working, &port2);
        pthread_detach(tid2);
    }
    pthread_exit(NULL);


    return 0;
}
