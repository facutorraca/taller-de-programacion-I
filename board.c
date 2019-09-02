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
        if(board->squares[i].number != '0') {
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

int board_put_number(board_t* board, char num, char row, char col) {
    int pos = (((row - '0') - 1) * 9 + (col - '0')) - 1;
    printf("%i\n",pos);
    if(board->squares[pos].fixed) {
        return ERROR;
    }
    board->squares[pos].number = num;
    return SUCCESS;
}

int board_reset(board_t* board) {
    for (int i = 0; i < CANT_SQUARES; i++) {
        if(!board->squares[i].fixed) {
            board->squares[i].number = '0';
        }
    }
    return SUCCESS;
}
