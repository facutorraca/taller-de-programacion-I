#include "sudoku_server.h"
#include "sudoku.h"
#include "server.h"

#include <stdio.h>

#define SUCCESS 0
#define ERROR 1

int sudoku_control_receive(const char* buffer, int total_bytes) {
    if(total_bytes != 1 && total_bytes != 4) {
        return ERROR;
    }
    if(total_bytes == 1) {
        char frt_buf = (char)buffer[0];
        if(frt_buf != 'V' || frt_buf != 'R' || frt_buf != 'G') {
            return ERROR;
        }
    }
    return SUCCESS;
}

int sudoku_server_start(const char* port) {
    server_t server;
    server_init(&server, port);

    sudoku_t sudoku;
    sudoku_init(&sudoku);

    sudoku_server_t sudoku_server;
    sudoku_server.server = server;
    sudoku_server.sudoku = sudoku;

    server_start_to_listen(&sudoku_server.server);
    server_start_to_receive(&sudoku_server.server, sudoku_control_receive);
    return SUCCESS;
}
