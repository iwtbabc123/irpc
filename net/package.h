#ifndef __NET_PACKAGE_H__
#define __NET_PACKAGE_H__

#include <stdint.h>
#include "buffer.h"

namespace inet{

typedef struct{
	uint32_t length;
	uint16_t service_id;
	uint16_t command_id;
}Header;

class Package{

public:
	Package();
	~Package();

	unsigned char* GetBuffer();
	uint32_t GetLength();
	unsigned char* GetBodyData();
	uint32_t GetBodyLength();

	void WriteHeader();

	uint16_t GetServiceId(){return header_.service_id;}
	uint16_t GetCommandId(){return header_.command_id;}

	void SetServiceId(uint16_t service_id);
	void SetCommandId(uint16_t command_id);
	//直接写完整的package
	void WriteAll(uint16_t service_id, uint16_t command_id, unsigned char* buf, uint32_t len);
	//读一条package
	static Package* ReadPackage(unsigned char* buf, uint32_t len);
	static bool IsPackageAvailable(unsigned char* buf, uint32_t len, uint32_t& package_len);
//private:
	//void Write(unsigned char* buf, uint32_t len){buffer_.Write((void*)buf, len);}

private:
	Buffer buffer_;  //包含一个package的unsigned char*数据，包含header
	Header header_;
};

}

#endif