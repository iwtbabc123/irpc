#ifndef __NET_SOCKET_UTIL_H__
#define __NET_SOCKET_UTIL_H__

#include <arpa/inet.h>
#include <stdint.h>

namespace inet{

extern int netlib_setnonblocking(int sockfd);
extern int netlib_socket();
extern int netlib_reuse_port(int sockfd, bool on);
extern int netlib_bind(int sockfd, uint16_t port);
extern int netlib_accept(int sockfd);
extern int netlib_listen(int sockfd, int backlog);
extern int netlib_connect(int sockfd, const char* server_ip, uint16_t port);
extern int netlib_send(int sockfd, void* buf, int len);
extern int netlib_recv(int sockfd, void* buf, int len);

extern int netlib_eventfd();
extern int netlib_eventfd_write(int eventfd);
extern int netlib_eventfd_read(int eventfd);

}

#endif