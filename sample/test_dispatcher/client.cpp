#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "net_util.h"

using namespace irpc;

int main(){

	int sockfd = netlib_socket();
	int ret = netlib_connect(sockfd,"127.0.0.1", 8888);
	if (ret < 0){
		printf("error=%d\n",errno);
		return -1;
	}
	printf("success");
	sleep(1);
	char buff[] = "send something to server!";
	netlib_send(sockfd, buff, sizeof(buff));
	sleep(1);
	return 0;
}

//g++ client.cpp ../../rpc/net_util.cpp -I../../rpc -o ../../bin/client