#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "board.h"
#include "parser.h"

#define SUCCESS 0
#define ERROR 1

int board_get_square_values(char* numbers) {
    parser_t parser;
    parser_init(&parser, "board.txt");
    parser_process_file(&parser, numbers);
    return SUCCESS;
}

int board_complete_squares(board_t* board) {
    char numbers[CANT_SQUARES];
    board_get_square_values(numbers);
    for (int i = 0; i < CANT_SQUARES; i++) {
        board->squares[i].number = numbers[i];
        if(board->squares[i].number != 0) {
            board->squares[i].fixed = true;
        } else {
            board->squares[i].fixed = false;
        }
    }
    return SUCCESS;
}

int board_init(board_t* board) {
    board_complete_squares(board);
    return SUCCESS;
}

int board_get_numbers(board_t* board, char* buffer) {
    for (int i = 0; i < CANT_SQUARES; i++) {
        buffer[i] = board->squares[i].number;
    }
    return SUCCESS;
}
