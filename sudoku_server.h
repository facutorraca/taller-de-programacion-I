#ifndef _SUDOKU_SERVER_H_
#define _SUDOKU_SERVER_H_

#include "server_message.h"
#include "sudoku.h"
#include "server.h"

#define ERROR 1
#define SUCCESS 0

typedef struct sudoku_server {
    server_message_t server_msg;
    sudoku_t sudoku;
} sudoku_server_t;

int sudoku_server_start(const char* port);

#endif
