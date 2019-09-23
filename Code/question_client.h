#ifndef _QUESTION_CLIENT_H_
#define _QUESTION_CLIENT_H_

#include "instruction.h"
#include "sudoku.h"
#include <stdint.h>

uint32_t question_client_create(char* message, instruction_t* instruction);

#endif
