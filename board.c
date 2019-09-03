#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "board.h"
#include "square.h"
#include "parser.h"

#define SUCCESS 0
#define ERROR 1

int board_get_square_values(char* numbers) {
    parser_t parser;
    parser_init(&parser, "board.txt");
    parser_process_file(&parser, numbers);
    return SUCCESS;
}

int board_get_position(char row, char col) {
    return (((row - '0') - 1) * 9 + (col - '0')) - 1;
}

int board_get_numbers(board_t* board, char* buffer) {
    for (int i = 0; i < CANT_SQUARES; i++) {
        buffer[i] = square_get_number(&board->square[i]);
    }
    return SUCCESS;
}

int board_put_number(board_t* board, char num, char row, char col) {
    int pos = board_get_position(row, col);
    return square_put_number(&board->square[pos], num);
}

int board_complete_squares(board_t* board) {
    char numbers[CANT_SQUARES];
    board_get_square_values(numbers);
    for (int row = 0; row < CANT_SQUARES; row++) {
            square_init(&board->square[pos], numbers[pos]);
    }
    return SUCCESS;
}

int board_reset(board_t* board) {
    for (int i = 0; i < CANT_SQUARES; i++) {
        square_reset(&board->square[i]);
    }
    return SUCCESS;
}

int board_init(board_t* board) {
    board_complete_squares(board);
    return SUCCESS;
}
