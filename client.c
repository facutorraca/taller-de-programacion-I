#include "client.h"
#include "socket.h"
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#define ERROR -1
#define SUCCESS 0

int client_start(client_t* client) {
    socket_connect(&client->c_socket, client->host, client->port);
    
    return SUCCESS;
}

int client_init(const char* host, const char* port) {
    //server initalized on the stack
    client_t client;
    socket_init(&client.c_socket);
    client.host = host;
    client.port = port;

    //Memory direction of client
    client_start(&client);
    return SUCCESS;
}
