#include "sudoku.h"
#include "board.h"
#include "server.h"

#include <stdio.h>

#define SUCCESS 0
#define ERROR 1

int sudoku_init_as_server(int argc, char const* argv[]) {
    board_t* board = board_create();
    server_init(argv[2]);
    return SUCCESS;
}

int sudoku_init_as_client(int argc, char const* argv[]) {
    return SUCCESS;
}
