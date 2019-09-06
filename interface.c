#include <stdio.h>
#include <string.h>
#include "message.h"
#include "sudoku.h"
#include "verifier.h"
#include <stdbool.h>

#define SUCCESS 0
#define ERROR 1
#define MAX_ROW 19
#define MAX_COL 37

void print_no_valid_command(){
    fprintf(stderr, "El comando instroducido no es valido\n");
}

void print_no_valid_position(){
    fprintf(stderr, "Error en los índices. Rango soportado: [1,9]\n");
}

void print_no_valid_number() {
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

int verify_put_inst(char* s1, char* s2, int i1, int i2, int i3) {
    if(strcmp(s1,"put") != 0 && strcmp(s2,"in") != 0) {
        print_no_valid_command();
        return ERROR;
    }
    if(!sudoku_position_is_valid(i2, i3)) {
        print_no_valid_position();
        return ERROR;
    }
    if(!sudoku_number_is_valid(i1)) {
        print_no_valid_number();
        return ERROR;
    }
    return SUCCESS;
}

int find_inst_error(char* s1, char* s2, int i1, int i2, int i3, int args) {
    if (args == 1) {
        bool is_get = (strcmp(s1, "get") == 0);
        bool is_rst = (strcmp(s1, "reset") == 0);
        bool is_vrf = (strcmp(s1, "verify") == 0);
        bool is_ext = (strcmp(s1, "exit") == 0);
        if (!is_get && !is_rst && !is_vrf && !is_ext) {
            print_no_valid_command();
            return ERROR;
        }
        return SUCCESS;
    } else if (args == 5) {
        return verify_put_inst(s1, s2, i1, i2, i3);
    }
    print_no_valid_command();
    return ERROR;

}

int verify_instuction(const char* inst) {
    char s1[10], s2[10];
    int i1 = 0, i2 = 0, i3 = 0;
    int num_args = sscanf(inst,"%s %i %s %i,%i", s1, &i1, s2, &i2, &i3);
    return find_inst_error(s1, s2, i1, i2, i3, num_args);
}

char interface_get_board_char(int row, int col, char next_number) {
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
        return next_number;
    }
    return ' ';
}

int interface_get_new_instruction(char* buffer, int len_buf) {
    bool inst_is_valid = false;
    while (!inst_is_valid) {
        if(!fgets(buffer, 20, stdin)) {
            return ERROR;
        }
        if(verify_instuction(buffer) == SUCCESS) {
            inst_is_valid = true;
        }
    }
    return SUCCESS;
}

int interface_get_board_design(char* buffer, char* numbers) {
    int n_pos = 0; //Position of the current number
    char line[MAX_COL] = {0};
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            char board_piece = interface_get_board_char(i, j, numbers[n_pos]);
            if(board_piece == numbers[n_pos]) {
                n_pos++;
            }
            if(board_piece == '0') {
                board_piece = ' ';
            }
            line[j] = board_piece;
        }
        strncat(buffer, line, MAX_COL);
        strncat(buffer, "\n", 1);
    }
    return SUCCESS;
}

int interface_conection_success() {
    printf("Conneccion establecida...\n");
    return SUCCESS;
}

int interface_print_message(message_t* msg) {
    return message_print(msg);
}
