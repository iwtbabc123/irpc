#include "rpc_server.h"

namespace irpc{

RpcServer::StartServer(uint16_t port){
	dispatcher_.StartServer(port);
}

}