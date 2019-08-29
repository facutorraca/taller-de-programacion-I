#ifndef _SERVER_H_
#define _SERVER_H_

#include "socket.h"

typedef struct server {
    const char* port;
    socket_t acceptor;
    socket_t connection;
} servet_t;

int server_init(const char* port);

#endif
