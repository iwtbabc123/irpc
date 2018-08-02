#include "dispatcher.h"

using namespace irpc;

int main(){
	Dispatcher dispatcher;
	dispatcher.StartServer(8888);
	return 0;
}

//g++ test_dispatcher_server.cpp ../rpc/dispatcher.cpp -Irpc -o ../bin/test_dispatcher_server