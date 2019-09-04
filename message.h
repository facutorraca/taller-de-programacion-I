#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_BUFFER 708

typedef struct message {
    char buffer[MAX_BUFFER];
    uint32_t len_msg;
} message_t;

int message_init(message_t* msg);

int message_create(message_t* msg, const char* str, uint32_t len);

int message_append_character(message_t* msg, char character);

uint32_t message_get_length(message_t* msg);

char message_get_first_character(message_t* msg);

int message_copy_in_buffer(message_t* msg, char* buffer, int len_buff);

int message_concat(message_t* frt, message_t* scd);

int message_get_nfirst(message_t* msg, char* buffer, int n);

int message_append_string(message_t* msg, char* str, int len);

char* message_get(message_t* msg);

#endif
