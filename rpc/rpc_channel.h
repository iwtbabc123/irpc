#ifndef __IRPC_RPC_CHANNEL_H__
#define __IRPC_RPC_CHANNEL_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <google/protobuf/service.h>

namespace irpc{

class RpcChannel : public ::google::protobuf::RpcChannel{

public:
	RpcChannel(int sockfd);

	virtual ~RpcChannel();

	virtual void CallMethod(const ::google::protobuf::MethodDescriptor* method,
            ::google::protobuf::RpcController* /* controller */,
            const ::google::protobuf::Message* request,
            ::google::protobuf::Message* response,
            ::google::protobuf::Closure*);

private:
	int sockfd_;
};

}

#endif