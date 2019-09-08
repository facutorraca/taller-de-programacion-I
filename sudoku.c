#include "sudoku.h"
#include "board.h"
#include "stdio.h"
#include <stdbool.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR 1

int sudoku_init(sudoku_t* sudoku) {
    return board_init(&sudoku->board);
}

char* sudoku_get_board_drawing(sudoku_t* sudoku) {
    return board_get_drawing(&sudoku->board);
}

int sudoku_put_number(sudoku_t* sudoku, char num, char row, char col) {
    return board_put_number(&sudoku->board, num, row, col);
}

int sudoku_reset(sudoku_t* sudoku) {
    return board_reset(&sudoku->board);
}

int sudoku_verify(sudoku_t* sudoku) {
    if (board_verify_row(&sudoku->board) == ERROR) {
        return ERROR;
    }
    if (board_verify_col(&sudoku->board) == ERROR) {
        return ERROR;
    }
    if (board_verify_box(&sudoku->board) == ERROR) {
        return ERROR;
    }
    return SUCCESS;
}
