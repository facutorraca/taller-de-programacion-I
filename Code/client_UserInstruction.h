#ifndef _USER_INSTRUCTION_H_
#define _USER_INSTRUCTION_H_

#include "client_Instruction.h"
#include <string>

class UserInstruction : public Instruction {
    public:
        UserInstruction(std::string args);

        ~UserInstruction();
};


#endif
