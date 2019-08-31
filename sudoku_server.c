#include "sudoku_server.h"
#include "sudoku.h"
#include "server.h"
#include <stdio.h>
#include <stdbool.h>

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

int sudoku_server_process_instructions(const char* buffer, sudoku_t* sudoku) {
    printf("Buffer: %s\n", buffer);
    return SUCCESS;
}

int sudoku_server_start(const char* port) {
    server_t server;
    server_init(&server, port);

    sudoku_t sudoku;
    sudoku_init(&sudoku);

    server_start_to_listen(&server);
    printf("Coneccion establecida\n");

    char buffer[4] = {0};
    bool connected = true;
    while (connected) {
        server_start_to_receive(&server, buffer, 4, sudoku_control_receive);
        sudoku_server_process_instructions(buffer, &sudoku);
    }
    return SUCCESS;
}
