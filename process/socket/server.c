#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH           "/home/wxx123/projects/test/process/socket/sock_server"
#define LISTEN_BACKLOG      50
int main()
{
    int sockfd, connfd;
    struct sockaddr_un listen_addr, accept_addr;
    int ret;
    char recv_buf[128];
    char write_buf[] = "this is server";
    socklen_t accept_addr_len;

    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(sockfd < 0) {
        printf("socket error\n");
        return -1;
    }

    unlink(SOCK_PATH);
    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sun_family = AF_LOCAL;
    strncpy(listen_addr.sun_path, SOCK_PATH, sizeof(listen_addr.sun_path) - 1);
    if(bind(sockfd, (struct sockaddr *) &listen_addr, sizeof(struct sockaddr_un)) < 0) {
        printf("bind error\n");
        close(sockfd);
        return -1;
    }

    if(listen(sockfd, LISTEN_BACKLOG) < 0) {
        printf("listen error\n");
        close(sockfd);
        return -1;
    } 

    connfd = accept(sockfd, (struct sockaddr *) &accept_addr, &accept_addr_len);
    if(connfd < 0) {
        printf("accept error\n");
        close(sockfd);
        return -1;
    }
    while(1) {
        ret = read(connfd, recv_buf, sizeof(recv_buf));
        if(ret < 0) {
            printf("read error\n");
            close(connfd);
            close(sockfd);
            return -1;
        }
        else if(0 == ret) {
            printf("client disconnected\n");
            close(connfd);
            close(sockfd);
            return -1;

        }
        else {
            printf("server recived data: %s\n", recv_buf);
        }

        ret = write(connfd, write_buf, strlen(write_buf));
        if(ret < 0) {
            printf("write error\n");
            close(connfd);
            close(sockfd);
            return -1;
        }
        else if(0 == ret) {
            printf("client disconnected\n");
            close(connfd);
            close(sockfd);
            return -1;
        }

        //break;
    } 
    return 0;
}
