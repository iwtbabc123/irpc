#include "tcp_server.h"
#include "acceptor.h"
#include "dispatcher.h"

namespace inet{

TcpServer::TcpServer(Dispatcher* dispatcher):
		dispatcher_(dispatcher){

}

TcpServer::~TcpServer(){

}

void TcpServer::start(){
	
}

}