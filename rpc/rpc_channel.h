#ifndef __IRPC_RPC_CHANNEL_H__
#define __IRPC_RPC_CHANNEL_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <google/protobuf/service.h>

const TOTAL_HEAD_LEN = 8;
const HEAD_LENGTH = 4;
const HEAD_SERVER_IDX = 4;

namespace irpc{

class RpcChannel : public ::google::protobuf::RpcChannel{

public:
	RpcChannel(google::protobuf::Service* service, int socket);

	virtual void ~RpcChannel();

	virtual void CallMethod(const ::google::protobuf::MethodDescriptor* method,
            ::google::protobuf::RpcController* /* controller */,
            const ::google::protobuf::Message* request,
            ::google::protobuf::Message* response,
            ::google::protobuf::Closure*);

	//TODO,需要对tcp流进行切分
	void ReadData(const char* buffer, int len);

private:
	google::protobuf::Service* service_;

};

}

#endif