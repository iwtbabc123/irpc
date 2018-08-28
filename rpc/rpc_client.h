#ifndef __IRPC_CLIENT_H__
#define __IRPC_CLIENT_H__

#include "tcp_client.h"
#include "rpc_channel.h"

using namespace inet;

namespace irpc{

class RpcClient : public TcpClient{

public:
	RpcClient(Dispatcher* dispatcher, const char* ip, uint16_t port);

	virtual ~RpcClient();

	void HandlePackage(Channel* channel, Package* pack) override;
};

}
#endif