#ifndef __IRPC_CHANNEL_H__
#define __IRPC_CHANNEL_H__

#include <ev++.h>

namespace irpc{

class Channel{
public:
	Channel(int fd, ev::io* watcher);
	~Channel();

	ev::io* IoWatcher(){
		return watcher_;
	}

	void r_w_cb(ev::io& io_watcher, int revents);

private:
	int fd_;
	ev::io* watcher_;
};

}

#endif