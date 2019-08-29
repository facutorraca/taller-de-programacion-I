#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "socket.h"

typedef struct client {
    const char* host;
    const char* port;
    socket_t c_socket;
} client_t;

int client_init(const char* host, const char* port);

#endif
