#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>

#define MAX_BUFFER 705

typedef struct message {
    char buffer[MAX_BUFFER];
    int len_msg;
} message_t;

int message_init(message_t* msg);

int message_create(message_t* msg, const char* str, int len);

int message_append_character(message_t* msg, char character);

unsigned int message_get_length(message_t* msg);

char message_get_first_character(message_t* msg);

int message_copy_in_buffer(message_t* msg, char* buffer, int len_buff);

#endif
