#include <stdio.h>
#include "channel.h"
#include "dispatcher.h"
#include "socket_util.h"

namespace inet{

Channel::Channel(Dispatcher* dispatcher, int fd):dispatcher_(dispatcher),fd_(fd){
	printf("Channel construct\n");
}

Channel::~Channel(){
	printf("Channel destroy\n");
	io_watcher_.stop();
}

void Channel::start(){
	io_watcher_.set<Channel, &Channel::OnEvent>(this);
	io_watcher_.start(fd_, ev::READ);
}

void Channel::OnEvent(ev::io& io_watcher, int revents){
	//int fd = watcher.fd;
	if (ev::ERROR & revents){
		return;
	}

	if (ev::READ & revents){
		OnRead();
	}
	if (EV_WRITE & revents){
		OnWrite();
	}
}

void Channel::OnRead(){
	char buffer[1024] = {0};

	int bytes = netlib_recv(fd_, buffer, 1024);
	printf("Dispatcher::OnRead %d bytes\n", bytes);
	if (bytes == 0){  //close
		//io_watcher_.stop();
		dispatcher_->DelConnection(fd_);
	}
	else if(bytes < 0){  //error
		//io_watcher_.stop();
		dispatcher_->DelConnection(fd_);
	}
	else{
		char* socket_data = (char*)malloc(sizeof(char) * bytes);
		memcpy(socket_data, buffer, bytes);
	}
}

void Channel::OnWrite(){

}

}