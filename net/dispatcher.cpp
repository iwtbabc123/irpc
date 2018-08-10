#include <stdio.h>
#include "dispatcher.h"
//#include "acceptor.h"

namespace inet{

Dispatcher::Dispatcher(uint16_t port):port_(port),acceptor_(nullptr){

}

void Dispatcher::loop(){
	acceptor_.reset(new Acceptor(this, port_));
	acceptor_->listen();
	loop_.run(0);
}

}