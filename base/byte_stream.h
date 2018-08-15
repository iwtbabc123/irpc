#ifndef __IRPC_BYTE_STREAM_H__
#define __IRPC_BYTE_STREAM_H__

#include <stdint.h>

namespace irpc{

class ByteStream{

public:
	ByteStream(char* buf, int len);
	~ByteStream(){}

private:
	char* buf_;
	uint32_t len_;

};

}

#endif