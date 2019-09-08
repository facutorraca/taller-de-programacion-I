#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "message.h"
#include <stdbool.h>

#define MAX_INST 20



int get_board_drawing(char* buffer);

bool verify_server_parameters(int argc, char const *argv[]);

bool verify_client_parameters(int argc, char const *argv[]);

void print_unsupported_mode_error();

void print_invalid_command_error();

void print_invalid_position_error();

void print_invalid_number_error();

void print_server_params_error();

void print_client_params_error();

void print_unsupported_mode_error();

void print_listening_error();

void print_binding_error();


#endif
