#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "message.h"

int interface_get_new_instruction(char* buffer, int len_buf);

int interface_get_board_design(char* buffer, char* numbers);

int interface_conection_success();

int interface_print_message(message_t* msg);

#endif
