#ifndef __NET_ACCEPTOR_H__
#define __NET_ACCEPTOR_H__

#include <stdint.h>
#include <ev++.h>
//#include "channel.h"

namespace inet{

class Dispatcher;

class Acceptor{

public:
	Acceptor(Dispatcher* dispatcher, uint16_t port);
	~Acceptor();

	void listen();

	void OnNewConnection(ev::io& watcher, int revents);

private:
	Dispatcher* dispatcher_;
	uint16_t port_;
	int fd_;
	ev::io io_watcher_;
	//Channel channel_;
	

};

}

#endif