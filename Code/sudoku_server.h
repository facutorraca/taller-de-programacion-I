#ifndef _SUDOKU_SERVER_H_
#define _SUDOKU_SERVER_H_

#include "server_message.h"
#include "sudoku.h"
#include "server.h"

typedef struct sudoku_server {
    server_message_t server_msg;
    sudoku_t sudoku;
} sudoku_server_t;

//Inicia el juego en modo servidor
int sudoku_run_as_server(const char* port);

#endif
