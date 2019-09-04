#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "socket.h"
#include "message.h"

#define ERROR 1
#define SUCCESS 0
#define MAX_BUFFER 723

typedef struct client {
    const char* host;
    const char* port;
    socket_t c_socket;
} client_t;

int client_start_to_recv(client_t* client, message_t* msg, uint32_t length_msg);

int client_start_to_send(client_t* server, message_t* msg);

int client_connect_with_server(client_t* client);

int client_init(client_t* client, const char* host, const char* port);

int client_release(client_t* client);

#endif
