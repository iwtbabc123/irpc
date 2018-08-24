#include <stdio.h>
#include "connector.h"
#include "socket_util.h"
#include "dispatcher.h"
#include "package.h"

namespace inet{

Connector::Connector(Dispatcher* dispatcher, const char* ip, uint16_t port):
		dispatcher_(dispatcher)/*,port_(port)*/{
			ip_ = ip;
			port_ = port;
}

Connector::~Connector(){
	
}

void Connector::connect(){
	int sockfd = netlib_socket();
	if (sockfd <= 0){
		exit(EXIT_FAILURE);
	}
	fd_ = sockfd;
	int ret = netlib_connect(fd_, ip_, port_);
	if (ret < 0){
		printf("CONNECT FAILED! errno=%d\n",errno);
		exit(EXIT_FAILURE);
	}

	io_watcher_.set<Connector, &Connector::OnEvent>(this);
	io_watcher_.start(fd_,ev::READ);
}

void Connector::OnEvent(ev::io& watcher, int revents){
	printf("OnEvent\n");
	if (ev::ERROR & revents){
		return;
	}

	if (ev::READ & revents){
		OnRead();
	}
}

void Connector::OnRead(){
	char buffer[1024] = {0};

	int bytes = netlib_recv(fd_, buffer, 1024);
	printf("Dispatcher::OnRead %d bytes\n", bytes);
	if (bytes == 0){  //close
		//dispatcher_->DelConnection(fd_);
	}
	else if(bytes < 0){  //error
		//dispatcher_->DelConnection(fd_);
	}
	else{
		in_buffer_.Write(buffer, bytes);

		Package* pack = nullptr;
		while(nullptr != (pack = Package::ReadPackage(in_buffer_.GetBuffer(), in_buffer_.GetWriteOffset()))){
			uint32_t package_len = pack->GetLength();
			
			//deal real package
			//printf("ReadPackage:%d,%d,%s\n",pack->GetServiceId(),pack->GetCommandId(),pack->GetBodyData());
			dispatcher_->HandlePackage(nullptr, pack);

			in_buffer_.Read(nullptr, package_len);
			delete pack;
			pack = nullptr;
		}
	}
}

void Connector::Send(void* data, int len){
	//out_buffer_.Write(data, len);
	//TODO
	int ret = netlib_send(fd_, (char*)data, len);
	if (ret <= 0){
		return;
	}
	printf("Channel::Send length=%d\n",ret);
}


}