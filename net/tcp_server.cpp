#include <stdio.h>
#include <functional>
#include "tcp_server.h"
#include "acceptor.h"
#include "dispatcher.h"
#include "package.h"

namespace inet{

TcpServer::TcpServer(Dispatcher* dispatcher, uint16_t port):
		dispatcher_(dispatcher),
		acceptor_(new Acceptor(dispatcher, port)){
}

TcpServer::~TcpServer(){

}

void TcpServer::start(){
	dispatcher_->setHandlePackageCB(std::bind(&TcpServer::HandlePackage, this, std::placeholders::_1, std::placeholders::_2));
	acceptor_->listen();
}

void TcpServer::HandlePackage(Channel* channel, Package* pack){
	printf("TcpServer::HandlePackage:%d,%d,%s\n",pack->GetServiceId(),pack->GetCommandId(),pack->GetBodyData());

	SendPackage(channel, pack);
}

void TcpServer::SendPackage(Channel* channel, Package* pack){
	dispatcher_->SendPackage(channel, pack);
}

}