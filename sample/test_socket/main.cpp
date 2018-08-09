#include <stdio.h>
#include <errno.h>
#include "socket_util.h"

using namespace inet;

int main(){
	printf("enter main\n");
	int fd;
	if ( 0 >= (fd = netlib_socket())){
		printf("netlib_socket error\n");
		return 0;
	}
	int ret;
	if ( 0 > (ret = netlib_bind(fd, 8888))){
		printf("netlib_bind error\n");
		return 0;
	}

	netlib_listen(fd,10);

	int conn_fd;

	while (true){
		conn_fd = netlib_accept(fd);
		if (conn_fd > 0){

		}
		else{
			printf("error no %d\n",errno);
		}
	}
	printf("end main\n");
	return 0;
}

//g++ main.cpp ../../net/socket_util.cpp -I../../net -o ../../bin/test_socket