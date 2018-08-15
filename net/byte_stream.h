#ifndef __NET_BYTE_STREAM_H__
#define __NET_BYTE_STREAM_H__

#include <stdint.h>

typedef unsigned char uchar;

namespace inet{

class ByteStream{

public:
	ByteStream(uchar* buf, uint32_t len);
	~ByteStream(){}

	//uchar* GetBuf() {}

	static int16_t ReadInt16(uchar* buf);
	static uint16_t ReadUInt16(uchar* buf);
	static int32_t ReadInt32(uchar* buf);
	static uint32_t ReadUInt32(uchar* buf);

	static void WriteInt16(uchar* buf, int16_t data);
	static void WriteUInt16(uchar* buf, uint16_t data);
	static void WriteInt32(uchar* buf, int32_t data);
	static void WriteUInt32(uchar* buf, uint32_t data);
	/*
	void operator << (int8_t data);
	void operator << (uint8_t data);
	void operator << (int16_t data);
	void operator << (uint16_t data);
	void operator << (int32_t data);
	void operator << (uint32_t data);

	void operator >> (int8_t& data);
	void operator >> (uint8_t& data);
	void operator >> (int16_t& data);
	void operator >> (uint16_t& data);
	void operator >> (int32_t& data);
	void operator >> (uint32_t& data);
	*/
private:
	uchar* buffer_;
	uint32_t len_;
	uint32_t pos_;

};

}

#endif