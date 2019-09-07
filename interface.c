#include <stdio.h>
#include <string.h>
#include "message.h"
#include "sudoku.h"
#include <stdbool.h>

#define SUCCESS 0
#define ERROR 1
#define MAX_ROW 19
#define MAX_COL 37

//arreglar
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
    fprintf(stderr,"Modo no soportado, el primer parámetro debe ser server o client\n");
}

void print_listening_error() {
    fprintf(stderr,"Error en LISTEN\n");
}

void print_binding_error() {
    fprintf(stderr,"Error en BIND\n");
}

bool verify_server_parameters(int argc, char const *argv[]) {
    //Faltan verificar mas cosas creo
    if (argc != 3) {
        print_server_params_error();
        return false;
    }
    return true;
}

bool verify_client_parameters(int argc, char const *argv[]) {
    //Faltan verificar mas cosas creo
    if (argc != 4) {
        print_client_params_error();
        return false;
    }
    return true;
}

char interface_get_board_char(int row, int col) {
    if (col == 0 || col == 12 || col == 24 || col == 36) {
        return 'U';
    }
    if (row == 0 || row == 6 || row == 12 || row == 18) {
        return '=';
    }
    if (col % 4 == 0 && row % 2 == 1 ) {
        return '|';
    }
    if (col % 4 == 0 && row % 2 == 0 ) {
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

int interface_get_board_drawing(char* buffer) {
    char line[MAX_COL] = {0};
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            line[j] = interface_get_board_char(i, j);
        }
        strncat(buffer, line, MAX_COL);
        strncat(buffer, "\n", 1);
    }
    return SUCCESS;
}
