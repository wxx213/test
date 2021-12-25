#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    char ip[24] = {"0.0.0.0"};
    
    if(argc > 1) {
	strcpy(ip, argv[1]);
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("error in create　socket");
        return 1;
    }

    inet_pton(AF_INET, ip ,&addr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("error in connect socket");
        return 1;
    }
    close(fd);
}
