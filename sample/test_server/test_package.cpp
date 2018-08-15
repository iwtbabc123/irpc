#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "package.h"

using namespace inet;

int main(){
	//Buffer buffer;
	unsigned char buf[] = "abcdefgh";
	Package* pack = new Package();
	pack->WriteAll(1,2, buf,(int)sizeof(buf));
	printf("sizeof buf=%d\n",(int)sizeof(buf));
	unsigned char* buffer = pack->GetBuffer();
	uint32_t len = pack->GetLength();
	printf("sizeof buf=%d\n",(int)sizeof(buf));
	Package* read = Package::ReadPackage(buffer, len);
	if (read == nullptr){
		printf("read package nullptr\n");
	}
	else{
		printf("read package %d, %d\n", read->GetServiceId(), read->GetCommandId());
		printf("%s\n",read->GetBodyData());
	}

	return 0;
}

//g++ test_package.cpp ../../net/byte_stream.cpp ../../net/buffer.cpp ../../net/package.cpp -I../../net -o ../../bin/test_package --std=c++11