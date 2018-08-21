#ifndef __NET_TCP_SERVER_H__
#define __NET_TCP_SERVER_H__

#include <stdint.h>
#include <memory>
#include "acceptor.h"

namespace inet{

class Dispatcher;

class Package;

class Channel;

class TcpServer{

public:
	TcpServer(Dispatcher* dispatcher, uint16_t port);
	virtual ~TcpServer();

	void start();

	virtual void HandlePackage(Channel* channel, Package* pack);

	virtual void SendPackage(Channel* channel, Package* pack);

private:
	Dispatcher* dispatcher_;
	std::unique_ptr<Acceptor> acceptor_;
};

}

#endif