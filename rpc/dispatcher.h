#ifndef __IRPC_DISPATCHER_H__
#define __IRPC_DISPATCHER_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ev.h>

namespace irpc{

class Dispatcher{

public:
	static Dispatcher& getInstance(){
		static Dispatcher instance;
		return instance;
	}

	void StartServer(uint16_t port);

	void OnAccept(int fd);
    void OnRead(int fd);
    void OnWrite(int fd);

	static void accept_cb(struct ev_loop* loop, struct ev_io* watcher, int revents);
    //接受客户端读写
    static void r_w_cb(struct ev_loop* loop, struct ev_io* watcher, int revents);
private:
	struct ev_loop* loop_;

};

}

#endif