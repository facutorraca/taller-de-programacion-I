#ifndef _SUDOKU_SERVER_H_
#define _SUDOKU_SERVER_H_

#include "sudoku.h"
#include "server.h"

typedef struct sudoku_server {
    sudoku_t sudoku;
    server_t server;
} sudoku_server_t;

int sudoku_server_start(const char* port);

#endif
