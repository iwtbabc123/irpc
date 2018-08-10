#ifndef __NET_CHANNEL_H__
#define __NET_CHANNEL_H__

#include <ev++.h>

namespace inet{

class Channel{

public:
	Channel();
	~Channel();

private:
	int fd_;
	ev::io* io_watcher_;

};

}

#endif