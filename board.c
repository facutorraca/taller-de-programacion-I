#include <stdbool.h>
#include <stdlib.h>
#include "board.h"
#include "parser.h"

#define COLUMNS 9
#define ROWS 9
#define SUCCESS 0
#define ERROR 1

int board_get_square_values(char** numbers) {
    parser_t parser;

    parser_init(&parser, "board.txt", numbers, " \n");
    parser_set_max_line_length(&parser, 18); //Including "\n"
    parser_process_file(&parser);
    return SUCCESS;
}

int board_complete_squares(board_t* board) {
    char* numbers[81];
    board_get_square_values(numbers);

    for(int i = 0; i < COLUMNS * ROWS; i++) {
        board->squares[i].number = (char)*numbers[i];
        if(board->squares[i].number != 0) {
            board->squares[i].fixed = true;
        } else {
            board->squares[i].fixed = false;
        }
    }
    return SUCCESS;
}

board_t* board_create() {
    board_t* board = (board_t*) malloc(sizeof(board_t));
    board->squares = (square_t*) malloc(COLUMNS * ROWS * sizeof(square_t));

    board_complete_squares(board);

    for(int i = 0; i < 81; i++) {
        printf("%c\n", board->squares[i].number);
    }

    return board;
}
