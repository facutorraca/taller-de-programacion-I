#ifndef _SERVER_H_
#define _SERVER_H_

#include "socket.h"

typedef struct server {
    const char* port;
    socket_t acceptor;
    socket_t s_socket;
} server_t;

int server_start_to_receive(server_t* server_t, int (*receive_control)(const char*, int));

int server_start_to_listen(server_t* server);

int server_init(server_t* server, const char* port);

#endif
