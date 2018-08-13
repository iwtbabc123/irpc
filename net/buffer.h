#ifndef __NET_BUFFER_H__
#define __NET_BUFFER_H__

#include <stdint.h>

namespace inet{

class Buffer{

public:
	Buffer();
	~Buffer();

	char* GetBuffer(){return buffer_;}
	uint32_t GetAllocSize(){return alloc_size_;}
	uint32_t GetWriteOffset(){return write_offset_;}
	void IncWriteOffset(uint32_t len){write_offset_+=len;}

	void Extend(uint32_t len);
	uint32_t Write(void* buf, uint32_t len);
	uint32_t Read(void* buf, uint32_t len);

private:
	char* buffer_;
	uint32_t alloc_size_;
	uint32_t write_offset_;

};

}

#endif