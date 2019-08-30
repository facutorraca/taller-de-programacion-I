#include "sudoku.h"
#include "server.h"

#define SUCCESS 0
#define ERROR 1

int sudoku_server_start(const char* port) {
    server_t server;
    server_init(&server, soportado);

    sudoku_t sudoku;
    sudoku_init(&sudoku)

    sudoku_server_t sudoku_server;
    sudoku_server.server = server;
    sudoku_server.sudoku = sudoku;

    server_start(&sudoku_server);
}

int sudoku_server_control_buffer(const char* buffer, int total_bytes) {
    if(total_bytes != 1 || total_bytes != 4) {
        return ERROR;
    }
    if(total_bytes == 1) {
        if(buffer[0] != "V" || buffer[0] != "R" || buffer[0] != "G") {
            return ERROR;
        }
    }
    return SUCCESS;
}

int sudoku_server_receive(sudoku_server_t* sudoku_server, char* buffer, int total_bytes) {
    if(sudoku_server_control_buffer(buffer, total_bytes) == ERROR) {
        return ERROR;
    }
    printf("Message recieve: %s\n", buffer);
    return SUCCESS;
}
