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

				unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char*) * (serialized_data.size()+1));
				strcpy((char*)data, serialized_data.c_str());
				package->WriteAll(idx, 1, data, serialized_data.size());

				unsigned char* data2 = package->GetBuffer();
				int ret = netlib_send(sockfd_, (void*)data2, package->GetLength());
				if (ret <= 0){
					return;
				}
			}
}