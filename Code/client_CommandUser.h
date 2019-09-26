#ifndef _COMMAND_USER_H_
#define _COMMAND_USER_H_

#include "client_Command.h"
#include <string>

class CommandUser : public Command {
    public:
        CommandUser(std::string args);

        ~CommandUser();
};


#endif
