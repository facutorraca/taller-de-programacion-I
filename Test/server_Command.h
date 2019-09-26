#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>

class Command {
    std::string cmd;

    public:
        Command(std::string cmd);

        void execute();

        ~Command();
};

#endif
