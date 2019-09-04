#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "client.h"
#include "socket.h"
#include "message.h"

int control_recv(message_t* msg);

int client_start_to_recv(client_t* client, message_t* msg, uint32_t length_msg) {
    char byte; //The message is capted byte by byte
    do {
        if(socket_receive(&client->c_socket, &byte, 1) == 1) {
            message_append_character(msg, byte);
        }
    } while (message_get_length(msg) != length_msg);
    return SUCCESS;
}

int client_start_to_send(client_t* client, message_t* msg) {
    int bytes_sent = 0, total_bytes = 0;
    do {
        bytes_sent = socket_send(&client->c_socket, msg->buffer, message_get_length(msg));
        total_bytes = bytes_sent + total_bytes;
    } while (msg->len_msg != total_bytes);
    return SUCCESS;
}

int client_connect_with_server(client_t* client) {
    socket_connect(&client->c_socket, client->host, client->port);
    return SUCCESS;
}

int client_init(client_t* client, const char* host, const char* port) {
    socket_init(&client->c_socket);
    client->host = host;
    client->port = port;
    return SUCCESS;
}
