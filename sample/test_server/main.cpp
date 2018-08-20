#include "dispatcher.h"
#include "tcp_server.h"

using namespace inet;

int main(){

	Dispatcher dispatcher(8888);
	TcpServer server(&dispatcher);
	server.start();
	dispatcher.loop();
	return 0;
}
