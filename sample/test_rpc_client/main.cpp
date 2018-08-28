#include "dispatcher.h"
#include "rpc_client.h"
#include "rpc_channel.h"
#include "package.h"
#include "echo_test.pb.h"

using namespace inet;
using namespace irpc;
using namespace echo;

int main(){
	Dispatcher dispatcher;
	RpcClient client(&dispatcher, "127.0.0.1", 8888);
	client.start();

	RpcChannel channel(client.ConnectFd());
	//MyRpcController controller;
	EchoService::Stub stub(&channel);
	RequestMessage request;
	ResponseMessage response;
	request.set_id(1);
	request.set_msg("abc");
	stub.echo(nullptr, &request, &response, nullptr);

	dispatcher.loop();
	return 0;
}
