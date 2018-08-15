#include "rpc_channel.h"

namespace irpc{

RpcChannel::RpcChannel(google::protobuf::Service* service){
	service_ = service;
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
				uint32_t total_len = serialzed_data.length() + 8;

				char s[total_len+1];
				snprintf(s, HEAD_LENGTH+1, "%s", (char*)&total_len);
				snprintf(s+HEAD_LENGTH, HEAD_SERVER_IDX+1, "%s", (char*)&idx);
				snprintf(s+TOTAL_HEAD_LEN, total_len + 1 - TOTAL_HEAD_LEN, "%s", serialized_data.c_str());

			}

void RpcChannel::ReadData(const char* buffer, int len){
	int index = 0;
	google::protobuf::Message* message;
	message->ParseFromString();

	google::protobuf::ServiceDescriptor* dispatcher = service_->GetDescriptor();
	google::protobuf::MethodDescriptor* method = dispatcher->method(index);

	service_->CallMethod(method, nullptr, message, nullptr, nullptr);
}



}