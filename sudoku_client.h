#ifndef _SUDOKU_CLIENT_H_
#define _SUDOKU_CLIENT_H_

#include "client_message.h"
#include "instruction.h"
#include "client.h"

#define SUCCESS 0
#define ERROR 1

typedef struct sudoku_client {
    client_message_t client_msg;
    instruction_t instruction;
} sudoku_client_t;

int sudoku_client_start(const char* host, const char* port);

#endif
