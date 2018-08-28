#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "rpc_server.h"
#include "package.h"
#include "rpc_controller.h"

namespace irpc{

RpcServer::RpcServer(Dispatcher* dispatcher, uint16_t port):TcpServer(dispatcher, port){

}

RpcServer::~RpcServer(){

}

void RpcServer::HandlePackage(Channel* channel, Package* pack){
	printf("RpcServer::HandlePackage:%d,%d,%s\n",pack->GetServiceId(),pack->GetCommandId(),pack->GetBodyData());
	uint16_t service_id = pack->GetServiceId();
	const ::google::protobuf::ServiceDescriptor* service_descriptor = service_->GetDescriptor();
	const ::google::protobuf::MethodDescriptor* method_descriptor = service_descriptor->method(service_id);
	
	::google::protobuf::Message* request = service_->GetRequestPrototype(method_descriptor).New();
	::google::protobuf::Message* response = service_->GetResponsePrototype(method_descriptor).New();
	std::string str((const char*)pack->GetBodyData());
	request->ParseFromString(str);
	RpcContrller rpc_controller;
	service_->CallMethod(method_descriptor, &rpc_controller, request, response, nullptr);
}

void RpcServer::RegisterService(::google::protobuf::Service* service){
	service_ = service;
}

}