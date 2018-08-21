#ifndef __NET_TCP_CLIENT_H__
#define __NET_TCP_CLIENT_H__

#include <stdint.h>
#include <memory>
#include <ev++.h>
#include "connector.h"

namespace inet{

class Dispatcher;

class Package;

class Channel;

class TcpClient{

public:
	TcpClient(Dispatcher* dispatcher, const char* ip, uint16_t port);
	virtual ~TcpClient();

	virtual void start();

	virtual void HandlePackage(Channel* channel, Package* pack);

	virtual void SendPackage(Package* pack);

protected:
	Dispatcher* dispatcher_;
	std::unique_ptr<Connector> connector_;
};

}

#endif