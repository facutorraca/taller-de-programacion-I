#include <stdio.h>
#include <string.h>
#include "message.h"

#define SUCCESS 0
#define ERROR 1
#define MAX_ROW 19
#define MAX_COL 37

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
    if(!fgets(buffer, len_buf, stdin)) {
        return ERROR;
    }
    return SUCCESS;
}

int interface_get_board_design(char* buffer, char* numbers) {
    int n_pos = 0; //Position of the current number
    char line[MAX_COL];
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            char board_char = interface_get_board_char(i, j, numbers[n_pos]);
            if(board_char == numbers[n_pos]) {
                n_pos++;
            }
            if(board_char == '0') {
                board_char = ' ';
            }
            line[j] = board_char;
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
