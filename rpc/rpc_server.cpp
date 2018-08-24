#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "rpc_server.h"
#include "package.h"

namespace irpc{

void RpcServer::HandlePackage(Channel* channel, Package* pack){
	uint16_t service_id = pack->GetServiceId();
	const ::google::protobuf::ServiceDescriptor* service_descriptor = service_->GetDescriptor();
	const ::google::protobuf::MethodDescriptor* method_descriptor = service_descriptor->method(service_id);
	
	::google::protobuf::Message* request = (&service_->GetRequestPrototype(method_descriptor))->New();
	::google::protobuf::Message* response = (&service_->GetResponsePrototype(method_descriptor))->New();
	std::string str((const char*)pack->GetBodyData());
	request->ParseFromString(str);
	service_->CallMethod(method_descriptor, nullptr, request, response, nullptr);
}

void RpcServer::RegisterService(::google::protobuf::Service* service){
	service_ = service;
}

}