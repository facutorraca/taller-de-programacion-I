#ifndef _COMMAND_PASS_H_
#define _COMMAND_PASS_H_

#include "client_Command.h"
#include <string>

class CommandPass : public Command {
    public:
        CommandPass(std::string args);

        ~CommandPass();
};


#endif
