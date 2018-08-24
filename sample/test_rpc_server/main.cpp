#include <string>
#include "echo_test.pb.h"


using namespace echo;

class EchoServiceImpl : public EchoService{

public:
	EchoServiceImpl(){}

	virtual void echo(::google::protobuf::RpcController* controller, const RequestMessage* request,ResponseMessage* response, ::google::protobuf::Closure* done){
		int id = request->id();
		std::string str = request->msg();
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