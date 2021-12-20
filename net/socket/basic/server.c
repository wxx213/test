#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main()
{
	char buffer[1024];
	int listen_fd,connect_fd,retval,i;
	int client_addr_len = 0;
	struct sockaddr_in local_addr,client_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	local_addr.sin_port = htons(9999);

	listen_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(listen_fd < 0){
		printf("socket error: %s\n",strerror(errno));
		return 0;
	}

	retval = bind(listen_fd,(struct sockaddr *)&local_addr,sizeof(struct sockaddr_in));
	if(retval < 0){
		printf("bind error: %s\n",strerror(errno));
		close(listen_fd);
		return 0;
	}

	retval = listen(listen_fd,10);
	if(retval < 0){
		printf("listen error: %s\n",strerror(errno));
		close(listen_fd);
		return 0;
	}
	connect_fd = accept(listen_fd,(struct sockaddr *)&client_addr,&client_addr_len);
	if(connect_fd < 0){
		printf("accept error: %s\n",strerror(errno));
		close(listen_fd);
		return 0;
	}
	sleep(5);
	close(connect_fd);
	close(listen_fd);
}
