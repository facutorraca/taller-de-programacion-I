#ifndef _QUESTION_CLIENT_H_
#define _QUESTION_CLIENT_H_

#include "instruction.h"
#include "message.h"
#include "sudoku.h"

int question_client_create(message_t* message, instruction_t* instruction);

#endif
