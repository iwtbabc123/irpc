#ifndef __NET_CONNECTOR_H__
#define __NET_CONNECTOR_H__

#include <stdint.h>
#include <ev++.h>
#include "buffer.h"
//#include "channel.h"

namespace inet{

class Dispatcher;

class Connector{

public:
	Connector(Dispatcher* dispatcher, const char* ip, uint16_t port);
	~Connector();

	void connect();

	void OnEvent(ev::io& watcher, int revents);
	void OnRead();

	void Send(void* data, int len);

	int Fd(){return fd_;}

private:
	Dispatcher* dispatcher_;
	const char* ip_;
	uint16_t port_;
	int fd_;
	ev::io io_watcher_;

	Buffer in_buffer_;  //read socket buffer
	Buffer out_buffer_;  //write to socket buffer
};

}

#endif