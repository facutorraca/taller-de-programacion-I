#ifndef _PASS_INSTRUCTION_H_
#define _PASS_INSTRUCTION_H_

#include "client_Instruction.h"
#include <string>

class PassInstruction : public Instruction {
    public:
        PassInstruction(std::string args);

        ~PassInstruction();
};


#endif
