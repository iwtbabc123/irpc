#ifndef __NET_CHANNEL_H__
#define __NET_CHANNEL_H__

#include <ev++.h>

namespace inet{

class Dispatcher;

class Channel{

public:
	Channel(Dispatcher* dispatcher, int fd);
	virtual ~Channel();

	void start();

	void OnEvent(ev::io& io_watcher, int revents);

	void OnRead();
	void OnWrite();

private:
	Dispatcher* dispatcher_;
	int fd_;
	ev::io io_watcher_;

};

}

#endif