#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "message.h"
#include <stdbool.h>

int interface_get_new_instruction(char* buffer, int len_buf);

int interface_get_board_drawing(char* buffer);

int interface_conection_success();

int interface_print_message(message_t* msg);

bool verify_server_parameters(int argc, char const *argv[]);

bool verify_client_parameters(int argc, char const *argv[]);

void print_unsupported_mode_error();

void print_listening_error();

void print_binding_error();

#endif
