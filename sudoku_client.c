#include "sudoku_client.h"
#include "client.h"
#include <stdbool.h>
#include <stdio.h>

#define SUCCESS 0
#define ERROR 1

int sudoku_client_process_instruction(const char* inst, char* buffer) {
    if((char)inst[0] == 'p') {
        buffer[0] = (char)inst[0];
        buffer[1] = (char)inst[4];
        buffer[2] = (char)inst[9];
        buffer[3] = (char)inst[11];
        return 4;
    } else if ((char)inst[0] == 'g') {
        buffer[0] = 'G';
    } else if ((char)inst[0] == 'v') {
        buffer[0] = 'V';
    } else if ((char)inst[0] == 'r') {
        buffer[0] = 'R';
    }
    return 1;
}

int sudoku_client_get_instruction(char* buffer) {
    char inst[12] = {0}; //Buffer for instructions
    printf("Ingrese un comando...\n");
    if (scanf("%s", inst) < 0) {
        return ERROR;
    };
    return sudoku_client_process_instruction(inst, buffer);
}

int sudoku_client_control_send(const char* buffer, int total_bytes) {
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

int sudoku_client_start(const char* host, const char* port) {
    client_t client;
    client_init(&client, host, port);
    client_connect_with_server(&client);

    char buffer[4] = {0};
    bool connected = true;
    while (connected) {
        int len_inst = sudoku_client_get_instruction(buffer);
        client_start_to_send(&client, buffer, len_inst, sudoku_client_control_send);
    }
    return SUCCESS;
}
