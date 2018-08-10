#ifndef __NET_DISPATCHER_H__
#define __NET_DISPATCHER_H__

#include <stdint.h>
#include <memory>
#include <ev++.h>
#include "acceptor.h"

namespace inet{

class Acceptor;

class Dispatcher{

public:
	Dispatcher(uint16_t port);

	void loop();

private:
	uint16_t port_;
	std::unique_ptr<Acceptor> acceptor_;
	ev::default_loop loop_;

};

}

#endif