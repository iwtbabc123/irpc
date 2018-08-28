#include <stdio.h>
#include <google/protobuf/message.h>
#include "rpc_channel.h"
#include "package.h"
#include "socket_util.h"

using namespace inet;

namespace irpc{

RpcChannel::RpcChannel(int sockfd):sockfd_(sockfd){
}

RpcChannel::~RpcChannel(){

}

void RpcChannel::CallMethod(const ::google::protobuf::MethodDescriptor* method,
            ::google::protobuf::RpcController* /* controller */,
            const ::google::protobuf::Message* request,
            ::google::protobuf::Message* response,
            ::google::protobuf::Closure*){
				std::string serialized_data = request->SerializeAsString();
				uint32_t idx = method->index();
				Package* package = new Package();

				int size = serialized_data.size();
				char* data = (char*)malloc(sizeof(char*) * (size+1));
				memcpy(data, serialized_data.c_str(), size);
				package->WriteAll(idx, 1, (unsigned char*)data, size);
				printf("RpcChannel::CallMethod:%d,%d,%s,%d",idx,1,data,size);
				free(data);
				unsigned char* buffer = package->GetBuffer();
				int ret = netlib_send(sockfd_, (void*)buffer, package->GetLength());
				if (ret <= 0){
					return;
				}
			}
}