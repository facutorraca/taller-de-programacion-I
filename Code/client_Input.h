#ifndef _INPUT_H_
#define _INPUT_H_

#include "client_Instruction.h"
#include "client_InstructionFactory.h"
#include <string>


class Input {
    InstructionFactory inst_factory;
    std::string input;

    private:
        void parse_input();

    public:
        Input();

        Instruction get_instruction();

        ~Input();
};

#endif
