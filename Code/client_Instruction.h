#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "client_ServerProxy.h"
#include <string>

class Instruction {
    std::string inst;

    public:
        Instruction(std::string inst);

        void send(ServerProxy* server);

        ~Instruction();
};

#endif
