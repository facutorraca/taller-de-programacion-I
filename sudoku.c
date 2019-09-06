#include "sudoku.h"
#include "board.h"
#include "stdio.h"
#include <stdbool.h>

#define SUCCESS 0
#define ERROR 1

int sudoku_init(sudoku_t* sudoku) {
    return board_init(&sudoku->board);
}

int sudoku_get_board_numbers(sudoku_t* sudoku, char* buffer) {
    return board_get_numbers(&sudoku->board, buffer);
}

int sudoku_put_number(sudoku_t* sudoku, char num, char row, char col) {
    return board_put_number(&sudoku->board, num, row, col);
}

int sudoku_reset(sudoku_t* sudoku) {
    return board_reset(&sudoku->board);
}

int sudoku_verify(sudoku_t* sudoku) {
    if(board_verify_row(&sudoku->board) == ERROR) {
        return ERROR;
    }
    if(board_verify_col(&sudoku->board) == ERROR) {
        return ERROR;
    }
    if(board_verify_box(&sudoku->board) == ERROR) {
        return ERROR;
    }
    return SUCCESS;
}

bool sudoku_number_is_valid(int number) {
    return number >= 1 && number <= 9;
}

bool sudoku_position_is_valid(int row, int col) {
    bool row_is_correct = (row >= 1 && row <= 9);
    bool col_is_correct = (col >= 1 && col <= 9);
    return row_is_correct && col_is_correct;
}
