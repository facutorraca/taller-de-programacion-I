#include "message.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int message_init(message_t* self) {
    self->len_msg = 0;
    memset(self->buffer, 0, MAX_LEN_MSG * sizeof(char));
    return SUCCESS;
}

int message_create(message_t* self, const char* str, uint32_t len) {
    if (len > MAX_LEN_MSG) {
        return ERROR;
    }
    for (int i = 0; i < len; i++){
        self->buffer[i] = str[i];
    }
    self->len_msg = len;
    return SUCCESS;
}

int message_append_character(message_t* self, char character) {
    if (self->len_msg >= MAX_LEN_MSG) {
        return ERROR;
    }
    self->buffer[self->len_msg] = character;
    self->len_msg++;
    return SUCCESS;
}

int message_print(message_t* self) {
    for (int i = 0; i < self->len_msg; i++) {
        fprintf(stdout, "%c", self->buffer[i]);
    }
    return SUCCESS;
}

uint32_t message_get_length(message_t* self) {
    return self->len_msg;
}

char message_get_first_character(message_t* self) {
    return self->buffer[0];
}

char* message_get(message_t* self) {
    return self->buffer;
}

int message_copy_in_buffer(message_t* self, char* buffer, int len_buff) {
    if (self->len_msg > len_buff) {
        return ERROR;
    }
    strncpy(buffer, self->buffer, self->len_msg);
    return SUCCESS;
}

int message_get_nfirst(message_t* self, char* buffer, int n) {
    if (self->len_msg > n) {
        return ERROR;
    }
    for (int i = 0; i < n; i++) {
        buffer[i] = self->buffer[i];
    }
    return SUCCESS;
}

int message_append_string(message_t* self, char* str, int len) {
    if (self->len_msg + len > MAX_LEN_MSG) {
        return ERROR;
    }
    if (len == 0) {
        return ERROR;
    }
    for (int i = self->len_msg; i < self->len_msg + len; i++) {
        self->buffer[i] = str[i - self->len_msg];
    }
    self->len_msg = self->len_msg + len;
    return SUCCESS;
}

int message_release(message_t* self) {
    self->len_msg = 0;
    memset(self->buffer, 0, MAX_LEN_MSG * sizeof(char));
    return SUCCESS;
}
