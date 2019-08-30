#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "socket.h"

typedef struct client {
    const char* host;
    const char* port;
    socket_t c_socket;
} client_t;

int client_start_to_send(client_t* server, const char* inst, int len_inst, int (*receive_control)(const char*, int));

int client_init(client_t* client, const char* host, const char* port);

int client_connect_with_server(client_t* client);

#endif
