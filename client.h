#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "socket.h"
#include "message.h"

typedef struct client {
    const char* host;
    const char* port;
    socket_t c_socket;
} client_t;

int client_start_to_send(client_t* server, message_t* msg);

int client_init(client_t* client, const char* host, const char* port);

int client_connect_with_server(client_t* client);

int client_start_to_recv(client_t* client, message_t* msg,  int (*control_recv)(message_t*));

#endif
