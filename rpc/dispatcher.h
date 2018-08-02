#ifndef __IRPC_DISPATCHER_H__
#define __IRPC_DISPATCHER_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ev++.h>

namespace irpc{

class Dispatcher{

public:
	/*
	static Dispatcher& getInstance(){
		static Dispatcher instance;
		return instance;
	}
	*/

	void StartServer(uint16_t port);

	void OnAccept(int fd);
    void OnRead(int fd, ev::io& io_watcher);
    void OnWrite(int fd, ev::io& io_watcher);

	void accept_cb(ev::io& io_watcher, int revents);
    //接受客户端读写
    void r_w_cb(ev::io& io_watcher, int revents);
private:
	ev::io io_watcher_;
	ev::default_loop loop_;


};

}

#endif