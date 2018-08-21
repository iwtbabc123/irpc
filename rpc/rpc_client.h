#ifndef __IRPC_CLIENT_H__
#define __IRPC_CLIENT_H__

#include "tcp_server.h"
#include "rpc_channel.h"

using namespace inet;

namespace irpc{

class RpcClient : public TcpClient{

public:
	RpcClient(Dispatcher* dispatcher, const char* ip, uint16_t port);

private:
	RpcChannel

};

}
#endif