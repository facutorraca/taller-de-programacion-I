#include "server.h"
#include "socket.h"

#define ERROR -1
#define SUCCESS 0

int server_init(const char* port) {
    socket_t acceptor;
    int rv_i, rv_b, rv_l;
    socket_init(&acceptor);
    socket_bind(&acceptor, port);
    socket_listen(&acceptor);
    //int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
}
