#ifndef _INPUT_H_
#define _INPUT_H_

#include "client_Command.h"
#include "client_CommandFactory.h"
#include <string>


class Input {
    CommandFactory cmd_factory;
    std::string input;

    private:
        void parse_input();

    public:
        Input();

        Command get_command();

        ~Input();
};

#endif
