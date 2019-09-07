#ifndef _ANSWER_SERVER_H_
#define _ANSWER_SERVER_H_

#include "message.h"
#include "sudoku.h"

int answer_server_create(message_t* message, sudoku_t* sudoku);

#endif
