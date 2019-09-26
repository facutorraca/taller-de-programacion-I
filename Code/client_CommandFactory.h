#ifndef _COMMAND_FACTORY_H_
#define _COMMAND_FACTORY_H_

#include "client_Command.h"
#include <string>

class CommnadFactory {
    std::string cmd;
    std::string arg;

    public:
        CommnadFactory();

        void set_argument(std::string args);

        void set_command(std::string inst);

        Instruction create_command();

        ~CommnadFactory();
};

#endif
