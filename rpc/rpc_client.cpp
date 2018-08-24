#include "rpc_client.h"
//#include "dispatcher.h"

namespace irpc{

RpcClient::RpcClient(Dispatcher* dispatcher, const char* ip, uint16_t port):TcpClient(dispatcher, ip, port){
}

}

