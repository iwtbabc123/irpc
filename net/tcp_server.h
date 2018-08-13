#ifndef __NET_TCP_SERVER_H__
#define __NET_TCP_SERVER_H__

#include <ev++.h>

namespace inet{

class Dispatcher;

class TcpServer{

public:
	TcpServer(Dispatcher* dispatcher);
	virtual ~TcpServer();

	void start();

private:
	Dispatcher* dispatcher_;
};

}

#endif