#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "client_ServerProxy.h"
#include <string>

class Commnad {
    std::string cmd;

    public:
        Commnad(std::string cmd);

        void execute(ServerProxy& server);

        ~Commnad();
};

#endif
