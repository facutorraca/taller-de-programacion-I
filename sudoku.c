#include "sudoku.h"
#include "board.h"

#define SUCCESS 0
#define ERROR 1

int sudoku_init(sudoku_t* sudoku) {
    sudoku->board = board_create();
    return SUCCESS;
}

int sudoku_get_board_numbers(sudoku_t* sudoku, char* buffer) {
    board_get_numbers(sudoku->board, buffer);
    return SUCCESS;
}
