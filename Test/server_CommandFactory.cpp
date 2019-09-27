#include "server_CommandFactory.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_CommandUser.h"
#include "server_CommandPass.h"
#include "server_CommandUnknown.h"
#include <string>

#include <iostream>

Command* CommandFactory::create_command() {
    if (this->cmd.compare("USER") == 0) {
        return new CommandUser(this->arg);
    }
    if (this->cmd.compare("PASS") == 0) {
        std::cout << "entre" << '\n';
        return new CommandPass(this->arg);
    }
    return new CommandUnknown();
}

void CommandFactory::set_command(std::string cmd) {
    this->cmd.assign(cmd);
}

void CommandFactory::set_argument(std::string arg) {
    this->arg.assign(arg);
}
