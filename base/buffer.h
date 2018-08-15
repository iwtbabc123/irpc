#ifndef __IRPC_BUFFER_H__
#define __IRPC_BUFFER_H__

#include <stdint.h>

namespace irpc{

class Buffer{

public:
	Buffer();
	~Buffer();

	

private:
	char* buffer_;
	uint32_t alloc_size_;
	uint32_t write_offset_;

};

}

#endif