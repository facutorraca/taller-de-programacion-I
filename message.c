#include "message.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define ERROR 1
#define SUCCESS 0

int message_init(message_t* msg) {
    msg->len_msg = 0;
    for (int i = 0; i < MAX_BUFFER_MSG; i++){
        msg->buffer[i] = 0;
    }
    return SUCCESS;
}

int message_create(message_t* msg, const char* str, uint32_t len) {
    if(len > MAX_BUFFER_MSG) {
        return ERROR;
    }
    for (int i = 0; i < len; i++){
        msg->buffer[i] = str[i];
    }
    msg->len_msg = len;
    return SUCCESS;
}

int message_append_character(message_t* msg, char character) {
    if(msg->len_msg >= MAX_BUFFER_MSG) {
        return ERROR;
    }
    msg->buffer[msg->len_msg] = character;
    msg->len_msg++;
    return SUCCESS;
}

int message_print(message_t* msg) {
    for (int i = 0; i < msg->len_msg; i++) {
        fprintf(stdout, "%c", msg->buffer[i]);
    }
    return SUCCESS;
}

uint32_t message_get_length(message_t* msg) {
    return msg->len_msg;
}

char message_get_first_character(message_t* msg) {
    return msg->buffer[0];
}

char* message_get(message_t* msg) {
    return msg->buffer;
}

int message_copy_in_buffer(message_t* msg, char* buffer, int len_buff) {
    if (msg->len_msg > len_buff) {
        return ERROR;
    }
    strncpy(buffer, msg->buffer, msg->len_msg);
    return SUCCESS;
}

int message_concat(message_t* frt, message_t* scd) {
    for (int i = 0; i < scd->len_msg; i++) {
        frt->buffer[i + frt->len_msg] = scd->buffer[i];
    }
    frt->len_msg = frt->len_msg + scd->len_msg;
    return SUCCESS;
}

int message_get_nfirst(message_t* msg, char* buffer, int n) {
    if(msg->len_msg > n) {
        return ERROR;
    }
    for(int i = 0; i < n; i++) {
        buffer[i] = msg->buffer[i];
    }
    return SUCCESS;
}

int message_append_string(message_t* msg, char* str, int len) {
    if (msg->len_msg + len > MAX_BUFFER_MSG) {
        return ERROR;
    }
    if (len == 0) {
        return ERROR;
    }
    for (int i = msg->len_msg; i < msg->len_msg + len; i++) {
        msg->buffer[i] = str[i - msg->len_msg];
    }
    msg->len_msg = msg->len_msg + len;
    return SUCCESS;
}
