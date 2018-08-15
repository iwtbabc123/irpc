#include <stdio.h>
#include "acceptor.h"
#include "socket_util.h"
#include "dispatcher.h"

namespace inet{

Acceptor::Acceptor(Dispatcher* dispatcher, uint16_t port):
		dispatcher_(dispatcher),port_(port){
}

Acceptor::~Acceptor(){

}

void Acceptor::listen(){
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

	if(netlib_bind(fd, port_) < 0){
		printf("netlib_bind error:%d\n",errno);
		exit(EXIT_FAILURE);
	}
	if (netlib_listen(fd,20)){
		printf("netlib_listen error:%d\n",errno);
		exit(EXIT_FAILURE);
	}

	fd_ = fd;

	io_watcher_.set<Acceptor, &Acceptor::NewConnectionCallback>(this);
	io_watcher_.start(fd_,ev::READ);
}

void Acceptor::NewConnectionCallback(ev::io& watcher, int revents){
	printf("NewConnectionCallback\n");
	if (ev::ERROR & revents){
		return;
	}

	OnAccept();

}

void Acceptor::OnAccept(){
	int conn_fd = netlib_accept(fd_);
	if (conn_fd < 0){
		printf("accept error\n");
	}

	netlib_setnonblocking(conn_fd);
	printf("netlib_setnonblocking %d\n",conn_fd);

	dispatcher_->NewConnection(conn_fd);
}

}