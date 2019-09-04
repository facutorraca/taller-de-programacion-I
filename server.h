#ifndef _SERVER_H_
#define _SERVER_H_

#include "socket.h"
#include "message.h"

#define ERROR 1
#define SUCCESS 0
#define MAX_BUFFER 723

typedef struct server {
    const char* port;
    socket_t acceptor;
    socket_t s_socket;
} server_t;

int server_start_to_recv(server_t* server, message_t* msg, int (*control_recv)(message_t*) );

int server_start_to_send(server_t* server, message_t* msg);

int server_start_to_listen(server_t* server);

int server_init(server_t* server, const char* port);

int server_release(server_t* server);

#endif
