#include <iostream>
#include <string>
#include "proto/echo_test.pb.h"

class MyEchoService :: public echo::IEchoService {
public:
	virtual void echo(::google::protobuf::RpcController* /* controller */,
                       const ::echo::EchoRequest* request,
                       ::echo::EchoResponse* response,
                       ::google::protobuf::Closure* done) {
      std::cout << request->msg() << std::endl;
      response->set_msg(
              std::string("I have received '") + request->msg() + std::string("'"));
      done->Run();
  }
};

class MyServer {

public:
	void Start(MyEchoService* service, const char* ip, int port){
		echo_service = service;
	}


private:
	Dispatcher dispatcher;
	MyEchoService* echo_service;

};



int main(){

	MyEchoService echo_service;
	MyServer server;
	server.Start(&echo_service,"127.0.0.1", 6688);

}