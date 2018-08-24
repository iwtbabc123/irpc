#ifndef __IRPC_RPC_SERVER_H__
#define __IRPC_RPC_SERVER_H__

#include <google/protobuf/service.h>
#include "tcp_server.h"

using namespace inet;

namespace irpc{

class RpcServer:public TcpServer{

public:
	RpcServer(Dispatcher* dispatcher, uint16_t port);

	virtual ~RpcServer();

	void HandlePackage(Channel* channel, Package* pack) override;

	void RegisterService(::google::protobuf::Service* service);

private:
	::google::protobuf::Service* service_;

};

}

#endif