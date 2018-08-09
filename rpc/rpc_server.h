#ifndef __IRPC_RPC_SERVER_H__
#define __IRPC_RPC_SERVER_H__

#include "dispatcher.h"

namespace irpc{

class RpcServer{
public:
	void StartServer(uint16_t port);

private:
	Dispatcher dispatcher_;
};

}

#endif