#ifndef __IRPC_MESSAGE_INFO_H__
#define __IRPC_MESSAGE_INFO_H__

#include <stdint.h>
#include "byte_stream.h"

namespace irpc{

class MessageInfo{

public:
	MessageInfo();
	~MessageInfo();

	char* GetBuffer();
	uint32_t GetLength();
	char* GetBodyData();
	uint32_t GetBodyLength();

	uint16_t GetServiceId() {}
	void SetServiceId(uint16_t service_id);
	void SetMsg(const char* buf);

private:
	ByteStream byte_stream_;

};

}
#endif