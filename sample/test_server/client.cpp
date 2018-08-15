#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "socket_util.h"
#include "package.h"

using namespace inet;

int main(){

	int sockfd = netlib_socket();
	int ret = netlib_connect(sockfd,"127.0.0.1", 8888);
	if (ret < 0){
		printf("error=%d\n",errno);
		return -1;
	}
	printf("success");
	sleep(1);
	//char buff[] = "send something to server!";

	unsigned char buf[] = "abcdefgh";
	Package* pack = new Package();
	pack->WriteAll(1,2, buf,(int)sizeof(buf));
	unsigned char* buffer = pack->GetBuffer();

	netlib_send(sockfd, (void*)buffer, pack->GetLength());

	unsigned char buf2[] = "abcdefgh";
	Package* pack2 = new Package();
	pack2->WriteAll(1,3, buf2,(int)sizeof(buf));
	unsigned char* buffer2 = pack2->GetBuffer();
	netlib_send(sockfd, (void*)buffer2, pack2->GetLength());
	sleep(1);
	return 0;
}

//g++ client.cpp ../../net/socket_util.cpp ../../net/buffer.cpp ../../net/byte_stream.cpp ../../net/package.cpp -I../../net -o ../../bin/client --std=c++11