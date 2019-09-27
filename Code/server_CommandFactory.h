#ifndef _COMMAND_FACTORY_H_
#define _COMMAND_FACTORY_H_

#include "server_Command.h"
#include <string>

class CommandFactory {
    std::string cmd;
    std::string arg;

    public:
        Command* create_command();

        void set_command(std::string cmd);

        void set_argument(std::string arg);
};

#endif
