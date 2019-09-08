
#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "client.h"
#include "socket.h"
#include "message.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_BUFFER 722

int control_recv(message_t* msg);

int client_recv(client_t* client, message_t* msg, uint32_t length_msg) {
    char buffer[MAX_BUFFER];
    int total_bytes = 0, bytes_recv = 0, rem_bytes;
    while (message_get_length(msg) != length_msg) {
        rem_bytes = length_msg - total_bytes;
        bytes_recv = socket_receive(&client->c_socket,
                                    &buffer[total_bytes],
                                    rem_bytes);
        message_append_string(msg, &buffer[total_bytes], bytes_recv);
        total_bytes = total_bytes + bytes_recv;
    }
    return total_bytes;
}

int client_send(client_t* client, message_t* msg) {
    char* msg_buf = message_get(msg);
    int bytes_sent = 0, total_bytes = 0, rem_bytes;
    while (message_get_length(msg) != total_bytes) {
        rem_bytes = message_get_length(msg) - total_bytes;
        bytes_sent = socket_send(&client->c_socket,
                                 (uint8_t*)&msg_buf[total_bytes],
                                 rem_bytes);
        total_bytes = bytes_sent + total_bytes;
    }
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

int client_release(client_t* client) {
    return socket_release(&client->c_socket);
}
