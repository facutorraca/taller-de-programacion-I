#include "client.h"
#include "socket.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/types.h>

#define ERROR -1
#define SUCCESS 0

int client_start_to_send(client_t* client) {
    char buffer[4] = {0};   //Initialize buffer

    bool continue_sending = true;
    while(continue_sending) {
        socket_send(&client->c_socket, buffer, 4);
    }
    return SUCCESS;
}

int client_start(client_t* client) {
    socket_connect(&client->c_socket, client->host, client->port);

    client_start_to_send(client);
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
