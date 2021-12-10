#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

bool epollAddFd(int epollFd, int fd, enum EPOLL_EVENTS eventsType){
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = eventsType;
    int ret = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev);
    if(ret == -1){
        perror("epoll_ctl failed");
        return false;
    }
    return true;
}

bool epollDelFd(int epollFd, int fd){
    int ret = epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, NULL);
    if(ret == -1){
        perror("epoll_ctl failed");
        return false;
    }
    return true;
}

int setNonblock(int fd){
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option|O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void handleReadWrite(int fd)
{
    
}

int main()
{
    printf("server start!\n");
    
    //创建套接字
    int listenFd = socket(AF_INET, SOCK_STREAM,0);
    if(listenFd == -1){
        perror("create socket filed");
        exit(1);
    }

    //设定端口,IPV4协议
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(10000);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //设置端口复用
    int opt = 1;
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    //绑定端口
    int ret = -1;
    ret = bind(listenFd, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    if(ret == -1){
        perror("bind socker error");
        exit(1);
    }

    //监听端口
    ret = listen(listenFd, 64);//64位置为等待连接队列长度
    if(ret == -1){
        perror("listen socker error");
        exit(1);
    }

    //目前为止，已经有一个绑定并且监听listenFd这个文件描述符号，
    //之后，监听这个文件描述符，有连接操作则创建新的连接，
    //对新的连接产生的新文件描述符，则进行读写就绪监听，并回调相应读写事件

    //创建一个epoll模型
    int epollFd = epoll_create(100);
    if(epollFd == -1){
        perror("epoll_create failed");
        exit(1);
    }

    //往epoll实例里添加　写事件监听　和　对应文件描述符
    epollAddFd(epollFd, listenFd, EPOLLIN);
    
    //待检测事件集合
    struct epoll_event events[1024];
    int size = sizeof(events)/sizeof(struct epoll_event);

    //
    while(1)
    {
        int num = epoll_wait(epollFd, events, size, -1);
        for(int i=0; i<num; i++)
        {
            int curFd = events[i].data.fd;
            //如果是连接事件就绪
            if(curFd == listenFd)
            {
                int tempFd = accept(curFd, NULL, NULL);
                printf("连接事件就绪,新的Fd:%d\n", tempFd);
                setNonblock(tempFd);
                bool flag =  epollAddFd(epollFd, tempFd, (enum EPOLL_EVENTS)(EPOLLET|EPOLLIN));
                if(flag == false) {
                    printf("可能连接达到上限了,拒绝连接\n");
                    break;
                }
            }
            else
            {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));
                while(1)
                {
                    int len = recv(curFd, buffer, sizeof(buffer), 0);
                    if(len == 0)
                    {
                        epollDelFd(epollFd, curFd);
                        break;
                    }
                    else if(len>0)
                    {
                        send(curFd, buffer, len, 0);
                    }
                    else
                    {
                        if(errno == EAGAIN)
                        {
                            break;
                        }
                        else
                        {
                            perror("recv error!");
                            exit(1);
                        }
                    }
                }
            }
        }
    }


    return 0;
}
