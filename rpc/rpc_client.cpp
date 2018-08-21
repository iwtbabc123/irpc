#include "rpc_client.h"

namespace irpc{

RpcClient(Dispatcher* dispatcher, const char* ip, uint16_t port):TcpClient(dispatcher, ip, port){

}

