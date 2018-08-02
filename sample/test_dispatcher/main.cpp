#include <stdlib.h>
#include "dispatcher.h"

using namespace irpc;

void siginthandler(int param)
{
  printf("User pressed Ctrl+C\n");
  exit(1);
}

int main(){
	signal(SIGINT, siginthandler);
    signal(SIGPIPE, SIG_IGN);

	Dispatcher& dispatcher = Dispatcher::getInstance();
	dispatcher.StartServer(8888);
	return 0;
}
