#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "byte_stream.h"

using namespace inet;

int main(){
	//Buffer buffer;
	unsigned char buf[] = "abcdefgh";
	ByteStream::WriteUInt16(buf, 11);
	ByteStream::WriteUInt16(buf+2, 12);
	ByteStream::WriteUInt32(buf+4, 4579);

	uint16_t a = ByteStream::ReadUInt16(buf);
	uint16_t b = ByteStream::ReadUInt16(buf+2);
	uint32_t c = ByteStream::ReadUInt32(buf+4);

	printf("==============> %d,%d,%d\n",a,b,c);
	/*
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
	*/
	return 0;
}

//g++ test_byte.cpp ../../net/byte_stream.cpp -I../../net -o ../../bin/test_byte --std=c++11