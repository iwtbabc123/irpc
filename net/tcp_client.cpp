#include <stdio.h>
#include <functional>
#include "tcp_client.h"
#include "connector.h"
#include "dispatcher.h"
#include "package.h"

namespace inet{

TcpClient::TcpClient(Dispatcher* dispatcher, const char* ip, uint16_t port):
		dispatcher_(dispatcher),
		connector_(new Connector(dispatcher, ip, port)){
	dispatcher_->setHandlePackageCB(std::bind(&TcpClient::HandlePackage, this, std::placeholders::_1, std::placeholders::_2));
}

TcpClient::~TcpClient(){

}

void TcpClient::start(){
	connector_->connect();  //TODO,改为nonblocking
}

void TcpClient::HandlePackage(Channel* channel, Package* pack){
	printf("TcpClient::HandlePackage:%d,%d,%s\n",pack->GetServiceId(),pack->GetCommandId(),pack->GetBodyData());

	//SendPackage(channel, pack);
}

void TcpClient::SendPackage(Package* pack){
	connector_->Send(pack->GetBuffer(), pack->GetLength());
}

}