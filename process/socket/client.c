#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH           "/home/wxx123/projects/test/process/socket/sock_server"

int main()
{
    int sockfd;
    struct sockaddr_un conn_addr;
    int ret;
    char recv_buf[128];
    char send_buf[] = "this is client";
    socklen_t accept_addr_len;

    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(sockfd < 0) {
        printf("socket error\n");
        return -1;
    }

    //unlink(SOCK_PATH);
    memset(&conn_addr, 0, sizeof(conn_addr));
    conn_addr.sun_family = AF_LOCAL;
    strncpy(conn_addr.sun_path, SOCK_PATH, sizeof(conn_addr.sun_path) - 1);
    ret  = connect(sockfd, (struct sockaddr *) &conn_addr, sizeof(struct sockaddr_un));
    if(ret < 0) {
        printf("connect error\n");
        close(sockfd);
        return -1;
    }

    while(1) {
        ret = write(sockfd, send_buf, strlen(send_buf));
        if(ret < 0) {
            printf("write error\n");
            close(sockfd);
            return -1;
        }

        ret = read(sockfd, recv_buf, sizeof(recv_buf));
        if(ret < 0) {
            printf("read error\n");
            close(sockfd);
            return -1;
        }
        else if(0 == ret) {
            printf("server disconnected\n");
            close(sockfd);
            return -1;

        }
        else {
            printf("client recived data: %s\n", recv_buf);
            close(sockfd);
        }

        break;

    } 
    return 0;
}
