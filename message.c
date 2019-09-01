#include "message.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ERROR 1
#define SUCCESS 0

int message_init(message_t* msg) {
    msg->len_msg = 0;
    for (int i = 0; i < MAX_BUFFER; i++){
        msg->buffer[i] = 0;
    }
    return SUCCESS;
}

int message_create(message_t* msg, const char* str, int len) {
    if(len > MAX_BUFFER) {
        return ERROR;
    }
    strncpy(msg->buffer, str, len);
    return SUCCESS;
}

int message_append_character(message_t* msg, char character) {
    if(msg->len_msg >= MAX_BUFFER) {
        return ERROR;
    }
    msg->buffer[msg->len_msg] = character;
    msg->len_msg++;
    return SUCCESS;
}

unsigned int message_get_length(message_t* msg) {
    return msg->len_msg;
}

char message_get_first_character(message_t* msg) {
    return msg->buffer[0];
}

int message_copy_in_buffer(message_t* msg, char* buffer, int len_buff) {
    if (msg->len_msg > len_buff) {
        return ERROR;
    }
    strncpy(buffer, msg->buffer, msg->len_msg);
    return SUCCESS;
}
