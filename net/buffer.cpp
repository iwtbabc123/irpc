#include <string.h>
#include <stdlib.h>
#include "buffer.h"

namespace inet{

Buffer::Buffer(){
	buffer_ = nullptr;
	alloc_size_ = 0;
	write_offset_ = 0;
}

Buffer::~Buffer(){
	alloc_size_ = 0;
	write_offset_ = 0;
	if(buffer_){
		free(buffer_);
		buffer_ = nullptr;
	}
}

void Buffer::Extend(uint32_t len){
	alloc_size_ = write_offset_ + len;
	alloc_size_ += alloc_size_ >> 2;
	char* new_buf = (char*)realloc(buffer_, alloc_size_);
	buffer_ = new_buf;
}

uint32_t Buffer::Write(void* buf, uint32_t len){
	if(write_offset_ + len > alloc_size_){
		Extend(len);
	}
	if(buf){
		memcpy(buffer_ + write_offset_, buf, len);
	}
	write_offset_ += len;
	return len;
}

uint32_t Buffer::Read(void* buf, uint32_t len){
	if (len > write_offset_){
		len = write_offset_;
	}
	if(buf){
		memcpy(buf, buffer_, len);
	}
	write_offset_ -= len;
	memmove(buffer_, buffer_ + len, write_offset_);
	return len;
}

}