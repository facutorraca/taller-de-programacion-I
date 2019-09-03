#ifndef _SUDOKU_SERVER_H_
#define _SUDOKU_SERVER_H_

#include "sudoku.h"
#include "server.h"

#define ERROR 1
#define SUCCESS 0

typedef struct sudoku_server {
    sudoku_t sudoku;
    server_t server;
} sudoku_server_t;

int sudoku_server_start(const char* port);

#endif
