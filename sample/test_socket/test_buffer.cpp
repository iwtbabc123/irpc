#include <stdio.h>
#include <string.h>
#include "buffer.h"

using namespace inet;

int main(){
	Buffer buffer;
	char buf[] = "abcdefgh";
	buffer.Write(buf, 8);
	buffer.Write(buf, 8);
	char read_buf[1024] = {0};
	buffer.Read(read_buf, 4);
	printf("read_buffer:%s\n", read_buf);
	memset(read_buf, 0, sizeof(read_buf));
	buffer.Read(read_buf, 4);
	printf("read_buffer:%s\n", read_buf);
	memset(read_buf, 0, sizeof(read_buf));
	buffer.Read(read_buf, 4);
	printf("read_buffer:%s\n", read_buf);
	memset(read_buf, 0, sizeof(read_buf));
	buffer.Read(read_buf, 4);
	printf("read_buffer:%s\n", read_buf);

	return 0;
}

//g++ test_buffer.cpp ../../net/buffer.cpp -I../../net -o ../../bin/test_buffer --std=c++11