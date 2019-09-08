#include "message.h"
#include "instruction.h"
#include "sudoku.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int prepare_put_instruction(message_t* msg, instruction_t* inst) {
    message_append_character(msg, 'P');
    message_append_character(msg, instruction_get_row(inst));
    message_append_character(msg, instruction_get_col(inst));
    message_append_character(msg, instruction_get_num(inst));
    return SUCCESS;
}

int question_client_create(message_t* message, instruction_t* instruction) {
    if (instruction_is_get(instruction)) {
        return message_append_character(message, 'G');
    }
    if (instruction_is_verify(instruction)) {
        return message_append_character(message, 'V');
    }
    if (instruction_is_reset(instruction)) {
        return message_append_character(message, 'R');
    } /* put instruction case */
    return prepare_put_instruction(message, instruction);
}
