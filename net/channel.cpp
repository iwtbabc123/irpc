#include <stdio.h>
#include "channel.h"
#include "dispatcher.h"
#include "socket_util.h"
#include "package.h"

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
		//char* socket_data = (char*)malloc(sizeof(char) * bytes);
		//memcpy(socket_data, buffer, bytes);
		in_buffer_.Write(buffer, bytes);

		Package* pack = nullptr;
		while(nullptr != (pack = Package::ReadPackage(in_buffer_.GetBuffer(), in_buffer_.GetWriteOffset()))){
			uint32_t package_len = pack->GetLength();
			
			//deal real package
			//printf("ReadPackage:%d,%d,%s\n",pack->GetServiceId(),pack->GetCommandId(),pack->GetBodyData());
			dispatcher_->HandlePackage(pack);

			in_buffer_.Read(nullptr, package_len);
			delete pack;
			pack = nullptr;
		}
	}
}

void Channel::OnWrite(){
	/*
	int events = EV_READ;

	while(!(*channel)->empty())
	{
		auto mq = (*channel)->pop_front();

		LogDebug("EpollServer::OnWrite send_len %d\n", mq->Size());

		char* tmp = (char*)malloc(sizeof(char) * mq->Size());
		memcpy(tmp, mq->Buffer(), mq->Size());
		//TODO,只发送一部分mq，剩余的尚未处理
		int ret = netlib_send(fd, tmp, mq->Size());
		if (ret == -1)  //TODO,发送不成功要重新发送
		{
			LogWarning("netlib_send -1\n");
			events |= EV_WRITE;
			break;
		}
		else if (ret == 0)
		{	
			LogDebug("netlib_send 0\n");
			break;
		}
		else if (ret > 0)
		{
			LogDebug("netlib_send %d\n", ret);
		}
	}

	UpdateEvent(fd, events, channel);
	*/
}

}