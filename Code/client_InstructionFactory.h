#ifndef _INSTRUCTION_FACTORY_H_
#define _INSTRUCTION_FACTORY_H_

#include "client_Instruction.h"
#include <string>

class InstructionFactory {
    std::string inst;
    std::string args;

    public:
        InstructionFactory();

        void set_args(std::string args);

        void set_instruction(std::string inst);

        Instruction create_instruction();

        ~InstructionFactory();
};

#endif
