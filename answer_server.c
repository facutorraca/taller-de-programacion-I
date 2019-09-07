#include "utils.h"
#include "message.h"
#include "sudoku.h"

#define SIZE_BOARD 722
#define NUM_NUMBERS 81

int prepare_message_with_board(sudoku_t* sudoku, message_t* msg) {
    char* board_drawing = sudoku_get_board_drawing(sudoku);
    message_create(msg, board_drawing, SIZE_BOARD);
    return SUCCESS;
}

int create_answer_for_put(sudoku_t* sudoku, message_t* msg) {
    char* msg_buf = message_get(msg);
    if (sudoku_put_number(sudoku, msg_buf[3], msg_buf[1], msg_buf[2]) == SUCCESS) {
        message_init(msg); //Restart the message
        prepare_message_with_board(sudoku, msg);
    } else {
        message_init(msg); //Restart the message
        message_create(msg, "La celda indicada no es modificable\n", 36);
    }
    return SUCCESS;
}

int create_answer_for_reset(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    sudoku_reset(sudoku);
    prepare_message_with_board(sudoku, msg);
    return SUCCESS;
}

int create_answer_for_verify(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    if (sudoku_verify(sudoku) == SUCCESS) {
        message_create(msg, "OK\n", 3);
    } else {
        message_create(msg, "ERROR\n", 6);
    }
    return SUCCESS;
}

int create_answer_for_get(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    prepare_message_with_board(sudoku, msg);
    return SUCCESS;
}

int answer_server_create(message_t* msg, sudoku_t* sudoku) {
    if (message_get_first_character(msg) == 'G') {
        create_answer_for_get(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'V') {
        create_answer_for_verify(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'R') {
        create_answer_for_reset(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'P') {
        create_answer_for_put(sudoku, msg);
    }
    return SUCCESS;
}
