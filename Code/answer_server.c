#include "utils.h"
#include "sudoku.h"
#include <stdio.h>
#include <string.h>

#define SIZE_BOARD 722
#define MAX_LEN_MSG 722
#define LEN_MODIY_MSG 36
#define LEN_ERROR_MSG 6
#define LEN_OK_MSG 3

uint32_t prepare_message_with_board(sudoku_t* sudoku, char* msg) {
    char* board_drawing = sudoku_get_board_drawing(sudoku);
    strncpy(msg, board_drawing, SIZE_BOARD);
    return SIZE_BOARD;
}

uint32_t create_answer_for_put(sudoku_t* sudoku, char* msg) {
    if (sudoku_put_number(sudoku, msg[2], msg[0], msg[1]) == SUCCESS) {
        memset(msg, 0, MAX_LEN_MSG * sizeof(char));
        return prepare_message_with_board(sudoku, msg);
    } else {
        memset(msg, 0, MAX_LEN_MSG * sizeof(char));
        strncpy(msg, "La celda indicada no es modificable\n", LEN_MODIY_MSG);
        return LEN_MODIY_MSG;
    }
}

uint32_t create_answer_for_reset(sudoku_t* sudoku, char* msg) {
    memset(msg, 0, MAX_LEN_MSG * sizeof(char));
    sudoku_reset(sudoku);
    return prepare_message_with_board(sudoku, msg);
}

uint32_t create_answer_for_verify(sudoku_t* sudoku, char* msg) {
    memset(msg, 0, MAX_LEN_MSG * sizeof(char));
    if (sudoku_verify(sudoku) == SUCCESS) {
        strncpy(msg, "OK\n", LEN_OK_MSG);
        return LEN_OK_MSG;
    } else {
        strncpy(msg, "ERROR\n", LEN_ERROR_MSG);
        return LEN_ERROR_MSG;
    }
}

uint32_t create_answer_for_get(sudoku_t* sudoku, char* msg) {
    memset(msg, 0, MAX_LEN_MSG * sizeof(char));
    return prepare_message_with_board(sudoku, msg);
}

uint32_t answer_server_create(char* msg, sudoku_t* sudoku) {
    if (msg[0] == 'G') {
        return create_answer_for_get(sudoku, msg);
    }
    if (msg[0] == 'V') {
        return create_answer_for_verify(sudoku, msg);
    }
    if (msg[0] == 'R') {
        return create_answer_for_reset(sudoku, msg);
    }
    return create_answer_for_put(sudoku, msg);
}
