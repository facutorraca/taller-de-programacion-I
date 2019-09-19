#include "instruction.h"
#include "sudoku.h"
#include "utils.h"
#include <stdint.h>

uint32_t question_client_create(char* message, instruction_t* instruction) {
    if (instruction_is_get(instruction)) {
        message[0] = 'G';
        return 1;
    } else if (instruction_is_verify(instruction)) {
        message[0] = 'V';
        return 1;
    } else if (instruction_is_reset(instruction)) {
        message[0] = 'R';
        return 1;
    } else {
        message[0] = 'P';
        message[1] = instruction_get_row(instruction);
        message[2] = instruction_get_col(instruction);
        message[3] = instruction_get_num(instruction);
        return 4;
    }
}
