#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "client_ServerProxy.h"
#include <string>

class Command {
    std::string cmd;

    public:
        Command(std::string cmd);

        void execute(ServerProxy& server);

        ~Command();
};

#endif
