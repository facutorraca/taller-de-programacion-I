#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "sudoku.h"
#include "utils.h"
#include <stdbool.h>
#include <netdb.h>

#define MAX_BOARD_ROW 19
#define MAX_BOARD_COL 37

void print_invalid_command_error(){
    fprintf(stderr, "El comando introducido no es valido\n");
}

void print_invalid_position_error(){
    fprintf(stderr, "Error en los índices. Rango soportado: [1,9]\n");
}

void print_invalid_number_error() {
    fprintf(stderr, "Error en el valor ingresado. Rango soportado: [1,9]\n");
}

void print_server_params_error() {
    fprintf(stderr, "Uso: ./tp server <puerto>\n");
}

void print_client_params_error() {
    fprintf(stderr, "Uso: ./tp client <host> <puerto>\n");
}

void print_unsupported_mode_error() {
    fprintf(stderr,"Modo no soportado, el primer parámetro "
                    "debe ser server o client\n");
}

void print_getaddrinfo_error(int errcode) {
    fprintf(stderr,"Error en GETADDRINFO: %s\n", gai_strerror(errcode));
}

void print_invalid_socket_close() {
    fprintf(stderr,"Error: el socket es invalido\n");
}

void print_socket_error(char* func_error) {
    fprintf(stderr,"Error en %s: %s\n", func_error, strerror(errno));
}

void interface_print_message(char* msg, uint32_t len) {
    for (int i = 0; i < len; i++) {
        fprintf(stdout, "%c", msg[i]);
    }
}

bool verify_server_parameters(int argc, char const *argv[]) {
    if (argc != 3) {
        print_server_params_error();
        return false;
    }
    return true;
}

bool verify_client_parameters(int argc, char const *argv[]) {
    if (argc != 4) {
        print_client_params_error();
        return false;
    }
    return true;
}

char get_board_char(int row, int col) {
    if (col == 0 || col == 12 || col == 24 || col == 36) {
        return 'U';
    }
    if (row == 0 || row == 6 || row == 12 || row == 18) {
        return '=';
    }
    if (col % 4 == 0 && row % 2 == 1) {
        return '|';
    }
    if (col % 4 == 0 && row % 2 == 0) {
        return '+';
    }
    if (row % 2 == 0) {
        return '-';
    }
    if (col % 2 == 0 /*U and = cases are contemplated above*/) {
        return 'X';
    }
    return ' ';
}

int get_board_drawing(char* buffer) {
    char line[MAX_BOARD_COL] = {0};
    for (int i = 0; i < MAX_BOARD_ROW; i++) {
        for (int j = 0; j < MAX_BOARD_COL; j++) {
            line[j] = get_board_char(i, j);
        }
        strncat(buffer, line, MAX_BOARD_COL);
        strncat(buffer, "\n", 1);
    }
    return SUCCESS;
}
