#include "channel.h"

namespace irpc{

Channel::Channel(int fd, ev::io* watcher):fd_(fd):watcher_(watcher){

}

Channel::~Channel(){

}

}