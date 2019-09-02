#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "parser.h"

#define MAX_ROW 9
#define MAX_COL 9
#define SUCCESS 0
#define ERROR 1

int board_get_square_values(char* numbers) {
    parser_t parser;
    parser_init(&parser, "board.txt", numbers, " \n");
    parser_set_max_line_length(&parser, 18); //Including "\n"
    parser_process_file(&parser);
    return SUCCESS;
}

int board_complete_squares(board_t* board) {
    char numbers[CANT_SQUARES];
    board_get_square_values(numbers);
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            int pos = i * (MAX_COL - 1) + j;
            board->squares[pos] = numbers[pos];
            if(board->squares[i].number != 0) {
                board->squares[i].fixed = true;
            } else {
                board->squares[i].fixed = false;
            }
        }
    }
    return SUCCESS;
}

int board_init(board_t* board) {
    board_complete_squares(board);
    return SUCCESS;
}

int board_get_numbers(board_t* board, char* buffer) {
    for (int i = 0; i < COLUMNS * ROWS; i++) {
        buffer[i] = board->squares[i].number;
    }
    return SUCCESS;
}
