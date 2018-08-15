#include <stdio.h>
#include "dispatcher.h"
#include "package.h"

namespace inet{

Dispatcher::Dispatcher(uint16_t port):port_(port),acceptor_(nullptr){

}

void Dispatcher::loop(){
	acceptor_.reset(new Acceptor(this, port_));
	acceptor_->listen();
	loop_.run(0);
}

void Dispatcher::NewConnection(int fd){
	printf("Dispatcher::NewConnection\n");
	ChannelPtr ptr(new Channel(this, fd));
	ptr->start();
	channel_map_[fd] = std::move(ptr);
}

void Dispatcher::DelConnection(int fd){
	printf("Dispatcher::DelConnection\n");
	ChannelMap::iterator iter = channel_map_.find(fd);
	if (iter != channel_map_.end()){
		channel_map_.erase(fd);
	}
}

void Dispatcher::HandlePackage(Channel* channel, Package* pack){
	handlePackageCB_(channel, pack);
}

void Dispatcher::SendPackage(Channel* channel, Package* pack){
	channel->Send(pack->GetBuffer(), pack->GetLength());
}

}