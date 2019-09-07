#include "instruction.h"
#include "interface.h"
#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"

bool instruction_is_get(instruction_t* self) {
    return strcmp(self->instuction, "get\n") == 0;
}

bool instruction_is_verify(instruction_t* self) {
    return strcmp(self->instuction, "verify\n") == 0;
}

bool instruction_is_reset(instruction_t* self) {
    return strcmp(self->instuction, "reset\n") == 0;
}

bool instruction_is_exit(instruction_t* self) {
    return strcmp(self->instuction, "exit\n") == 0;
}

char instruction_get_row(instruction_t* self) {
    return self->instuction[9];
}

char instruction_get_col(instruction_t* self) {
    return self->instuction[11];
}

char instruction_get_num(instruction_t* self) {
    return self->instuction[4];
}

bool put_inst_has_error(char* s1, char* s2, int i1, int i2, int i3) {
    if (strcmp(s1,"put") != 0 || strcmp(s2,"in") != 0) {
        print_invalid_command_error();
        return true;
    }
    if(!sudoku_position_is_valid(i2, i3)) {
        print_invalid_position_error();
        return true;
    }
    if(!sudoku_number_is_valid(i1)) {
        print_invalid_number_error();
        return true;
    }
    return false;
}

bool instruction_has_error(char* s1, char* s2, int i1, int i2, int i3, int args) {
    if (args == 1) {
        bool is_get = (strcmp(s1, "get") == 0);
        bool is_rst = (strcmp(s1, "reset") == 0);
        bool is_vrf = (strcmp(s1, "verify") == 0);
        bool is_ext = (strcmp(s1, "exit") == 0);
        if(!is_get && !is_rst && !is_vrf && !is_ext) {
            print_invalid_command_error();
            return true;
        }
        return false;
    } else if (args == 5) {
        return put_inst_has_error(s1, s2, i1, i2, i3);
    } else {
        print_invalid_command_error();
        return true;
    }
}

int instruction_is_correct(const char* inst) {
    char s1[10], s2[10];
    int i1 = 0, i2 = 0, i3 = 0;
    int num_args = sscanf(inst,"%s %i %s %i,%i", s1, &i1, s2, &i2, &i3);
    return !(instruction_has_error(s1, s2, i1, i2, i3, num_args));
}

int instruction_get_new(instruction_t* self) {
    instruction_init(self); //Reset the buffer

    bool instruction_is_valid = false;
    while (!instruction_is_valid) {
        if(!fgets(self->instuction, MAX_LEN_INS, stdin)) {
            return ERROR;
        }
        if(instruction_is_correct(self->instuction)) {
            instruction_is_valid = true;
        }
    }
    return SUCCESS;
}

int instruction_init(instruction_t* self) {
    memset(self->instuction, 0, MAX_LEN_INS * sizeof(char));
    return SUCCESS;
}
