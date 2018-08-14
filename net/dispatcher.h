#ifndef __NET_DISPATCHER_H__
#define __NET_DISPATCHER_H__

#include <stdint.h>
#include <map>
#include <memory>
#include <ev++.h>
#include "acceptor.h"
#include "channel.h"

namespace inet{

class Acceptor;

typedef std::unique_ptr<Channel> ChannelPtr;

class Dispatcher{

public:
	Dispatcher(uint16_t port);

	void loop();

	void NewConnection(int fd);
	void DelConnection(int fd);

private:
	uint16_t port_;
	std::unique_ptr<Acceptor> acceptor_;
	ev::default_loop loop_;
	typedef std::map<int, ChannelPtr> ChannelMap;
	ChannelMap channel_map_;


};

}

#endif