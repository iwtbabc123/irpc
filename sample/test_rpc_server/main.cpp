#include <string>
#include <stdio.h>
#include <google/protobuf/service.h>
#include "echo_test.pb.h"
#include "dispatcher.h"
#include "rpc_server.h"

using namespace echo;
using namespace inet;
using namespace irpc;
//rpc service
class EchoServiceImpl : public EchoService{

public:
	EchoServiceImpl(){}

	void echo(::google::protobuf::RpcController* controller, const RequestMessage* request,ResponseMessage* response, ::google::protobuf::Closure* done){
		printf("EchoServiceImpl\n");
		if(request == nullptr){
			printf("Request is nullptr\n");
		}
		int id = request->id();
		std::string str = request->msg();
		printf("EchoServiceImpl::echo=%d,%s",id, str.c_str());
		response->set_id(id+1);
		response->set_msg(str);
	}

};

int main(int argc, char* argv[]){

	EchoServiceImpl* impl = new EchoServiceImpl();

	Dispatcher dispatcher;
	RpcServer server(&dispatcher, 8888);
	server.RegisterService(impl);
	server.start();
	dispatcher.loop();
	return 0;
}