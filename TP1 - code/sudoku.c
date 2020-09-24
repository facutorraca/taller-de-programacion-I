#include "sudoku.h"
#include "utils.h"
#include "board.h"
#include "stdio.h"
#include "parser.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define NUM_SQUARES 81
#define LINE_LENGHT 25

int sudoku_init(sudoku_t* self) {
    char numbers[NUM_SQUARES];
    memset(numbers, 0, NUM_SQUARES * sizeof(char));

    parser_t parser;
    parser_init(&parser, "board.txt", numbers, NUM_SQUARES);
    parser_process_file(&parser);
    parser_release(&parser);

    return board_init(&self->board, numbers);
}

char* sudoku_get_board_drawing(sudoku_t* self) {
    return board_get_drawing(&self->board);
}

int sudoku_put_number(sudoku_t* self, char num, char row, char col) {
    return board_put_number(&self->board, num,
                                          char_to_int(row),
                                          char_to_int(col));
}

int sudoku_reset(sudoku_t* self) {
    return board_reset(&self->board);
}

int sudoku_verify(sudoku_t* self) {
    if (board_verify_row(&self->board) == ERROR) {
        return ERROR;
    }
    if (board_verify_col(&self->board) == ERROR) {
        return ERROR;
    }
    if (board_verify_box(&self->board) == ERROR) {
        return ERROR;
    }
    return SUCCESS;
}

int sudoku_release(sudoku_t* self) {
    return board_release(&self->board);
}
