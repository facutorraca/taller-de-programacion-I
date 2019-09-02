#include "sudoku.h"
#include "board.h"
#include "stdio.h"

#define SUCCESS 0
#define ERROR 1

int sudoku_init(sudoku_t* sudoku) {
    board_init(&sudoku->board);
    return SUCCESS;
}

int sudoku_get_board_numbers(sudoku_t* sudoku, char* buffer) {
    board_get_numbers(&sudoku->board, buffer);
    return SUCCESS;
}

int sudoku_put_number(sudoku_t* sudoku, char num, char row, char col) {
    return board_put_number(&sudoku->board, num, row, col);
}
