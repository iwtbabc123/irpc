#include <stdlib.h>
#include <errno.h>
#include "dispatcher.h"
#include "net_util.h"

namespace irpc{

void Dispatcher::StartServer(uint16_t port){
	int fd = netlib_socket();
	if (fd < 0){
		printf("fd < 0\n");
		exit(EXIT_FAILURE);
	}
	netlib_setnonblocking(fd);

	struct linger linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;
	setsockopt(fd, SOL_SOCKET, SO_LINGER, (const char *) &linger, sizeof(linger));

	netlib_reuse_port(fd, true);

	if(netlib_bind(fd, port) < 0){
		printf("netlib_bind error:%d\n",errno);
		exit(EXIT_FAILURE);
	}
	if (netlib_listen(fd,20)){
		printf("netlib_listen error:%d\n",errno);
		exit(EXIT_FAILURE);
	}

	//loop_ = ev::default_loop();
	/*
	struct ev_io io_watcher;
	ev_init(&io_watcher, accept_cb);
	ev_io_set(&io_watcher, fd, EV_READ);
	ev_io_start(loop_, &io_watcher);

	printf("StartServer:%p\n",this);

	ev_run(loop_, 0);
	*/
	io_watcher_.set<Dispatcher, &Dispatcher::accept_cb>(this);
	io_watcher_.start(fd, ev::READ);
	loop_.run(0);
}

void Dispatcher::OnAccept(int fd){
	printf("EpollServer::OnAccept %d\n", fd);
	printf("StartServer:%p\n",this);

	int conn_fd = netlib_accept(fd);
	if (conn_fd < 0){
		printf("accept error\n");
	}

	netlib_setnonblocking(conn_fd);
	printf("netlib_setnonblocking %d\n",conn_fd);
	/*
	struct ev_io* conn_ev = (struct ev_io*) malloc(sizeof(struct ev_io));
	if (conn_ev == nullptr){
		printf("malloc error in accept_cb\n");
		return;
	}
	*/

	//ev::io* io_watcher = (ev::io*) malloc(sizeof(ev::io));
	ev::io* io_watcher = new ev::io;
	if (io_watcher == nullptr){
		printf("malloc error in accept_cb\n");
		return;
	}

	io_watcher->set<Dispatcher, &Dispatcher::r_w_cb>(this);
	io_watcher->start(conn_fd, ev::READ);
	
	/*
	ev_init(conn_ev, r_w_cb);
	ev_io_set(conn_ev, conn_fd, EV_READ);
	ev_io_start(loop_, conn_ev);
	*/
}

void Dispatcher::OnRead(int fd, ev::io& watcher){
	printf("Dispatcher::OnRead:%d\n", fd);

	char buffer[1024] = {0};

	int bytes = netlib_recv(fd, buffer, 1024);
	printf("Dispatcher::OnRead %d bytes\n", bytes);
	if (bytes == 0){  //close
		//ev_io_stop(loop_, watcher);
		watcher.stop();
	}
	else if(bytes < 0){  //error
		//ev_io_stop(loop_, watcher);
		watcher.stop();
	}
	else{
		char* socket_data = (char*)malloc(sizeof(char) * bytes);
		memcpy(socket_data, buffer, bytes);
		//std::string str_buf(buffer);
		//printf("Dispatcher::OnRead %d bytes\n", bytes);
		//MessageQueue::getInstance().MQ2S_Push(fd, fd_type, socket_data, bytes);

	}
}

void Dispatcher::OnWrite(int fd, ev::io& watcher){
	printf("EpollServer::OnWrite:%d\n",fd);
	/*
	UP_Channel* channel = this->GetChannel(fd, fd_type);
	if (channel == nullptr)
	{
		printf("EpollServer::OnWrite channel null\n");
		return;
	}

	int events = EV_READ;

	while(!(*channel)->empty())
	{
		auto mq = (*channel)->pop_front();

		printf("EpollServer::OnWrite send_len %d\n", mq->Size());

		char* tmp = (char*)malloc(sizeof(char) * mq->Size());
		memcpy(tmp, mq->Buffer(), mq->Size());
		//TODO,只发送一部分mq，剩余的尚未处理
		int ret = netlib_send(fd, tmp, mq->Size());
		if (ret == -1)  //TODO,发送不成功要重新发送
		{
			printf("netlib_send -1\n");
			events |= EV_WRITE;
			break;
		}
		else if (ret == 0)
		{	
			printf("netlib_send 0\n");
			break;
		}
		else if (ret > 0)
		{
			printf("netlib_send %d\n", ret);
		}

		UpdateEvent(fd, events, channel);
	}
	*/
}

void Dispatcher::accept_cb(struct ev::io& watcher, int revents){
	int fd = watcher.fd;

	if (ev::ERROR & revents){
		//LogDebug("error event in accept\n");
		return;
	}
	printf("accept_cb \n");
	OnAccept(fd);
}

void Dispatcher::r_w_cb(struct ev::io& watcher, int revents){
	int fd = watcher.fd;
	//LogDebug("r_w_cb %d,%d\n", fd, revents);
	if (ev::ERROR & revents){
		//LogError("error event in read or write\n");
		return;
	}

	if (ev::READ & revents){
		OnRead(fd, watcher);
	}
	if (EV_WRITE & revents){
		OnWrite(fd, watcher);
	}
}

}