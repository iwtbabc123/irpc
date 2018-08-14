#ifndef __NET_CHANNEL_H__
#define __NET_CHANNEL_H__

#include <ev++.h>
#include "buffer.h"

namespace inet{

class Dispatcher;

//typedef std::function<void()> ReadEventCallback;

class Channel{

public:
	Channel(Dispatcher* dispatcher, int fd);
	virtual ~Channel();

	void start();

	void OnEvent(ev::io& io_watcher, int revents);

	void OnRead();
	void OnWrite();

	//void SetReadCallback(ReadEventCallback cb){readCallack_ = std::move(cb);}

private:
	Dispatcher* dispatcher_;
	int fd_;
	ev::io io_watcher_;

	Buffer in_buffer_;  //read socket buffer
	Buffer out_buffer_;  //write to socket buffer

	//ReadEventCallback readCallack_;

};

}

#endif