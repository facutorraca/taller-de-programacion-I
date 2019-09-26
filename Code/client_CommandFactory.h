#ifndef _COMMAND_FACTORY_H_
#define _COMMAND_FACTORY_H_

#include "client_Command.h"
#include <string>

class CommandFactory {
    std::string cmd;
    std::string arg;

    public:
        CommandFactory();

        void set_argument(std::string args);

        void set_command(std::string inst);

        Command create_command();

        ~CommandFactory();
};

#endif
