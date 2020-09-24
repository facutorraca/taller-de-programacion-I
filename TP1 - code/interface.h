#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdbool.h>
#include <stdint.h>

int get_board_drawing(char* buffer);

bool verify_server_parameters(int argc, char const *argv[]);

bool verify_client_parameters(int argc, char const *argv[]);

void print_unsupported_mode_error();

void print_invalid_command_error();

void print_invalid_position_error();

void print_invalid_number_error();

void print_server_params_error();

void print_invalid_socket_close();

void print_client_params_error();

void print_unsupported_mode_error();

void print_getaddrinfo_error(int errcode);

void print_socket_error(char* func_error);

void interface_print_message(const char* msg, uint32_t len);

#endif
