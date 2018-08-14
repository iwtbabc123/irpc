#include "byte_stream.h"

namespace inet{

ByteStream::ByteStream(uchar* buf, uint32_t len){
	buffer_ = buf;
	len_ = len;
	pos_ = 0;
}

int16_t ByteStream::ReadInt16(uchar* buf){
	int16_t data = (buf[0] << 8) | buf[1];
	return data;
}

uint16_t ByteStream::ReadUInt16(uchar* buf){
	uint16_t data = (buf[0] << 8) | buf[1];
	return data;
}

int32_t ByteStream::ReadInt32(uchar* buf){
	int32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	return data;
}

uint32_t ByteStream::ReadUInt32(uchar* buf){
	uint32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	return data;
}

void ByteStream::WriteInt16(uchar* buf, int16_t data){
	buf[0] = (uchar)(data >> 8);
	buf[1] = (uchar)(data & 0xFF);
}

void ByteStream::WriteUInt16(uchar* buf, uint16_t data){
	buf[0] = (uchar)(data >> 8);
	buf[1] = (uchar)(data & 0xFF);
}

void ByteStream::WriteInt32(uchar* buf, int32_t data){
	buf[0] = (uchar)(data >> 24);
	buf[1] = (uchar)((data >> 16) & 0xFF);
	buf[2] = (uchar)((data >> 8) & 0xFF);
	buf[3] = (uchar)(data & 0xFF);
}

void ByteStream::WriteUInt32(uchar* buf, uint32_t data){
	buf[0] = (uchar)(data >> 24);
	buf[1] = (uchar)((data >> 16) & 0xFF);
	buf[2] = (uchar)((data >> 8) & 0xFF);
	buf[3] = (uchar)(data & 0xFF);
}

}