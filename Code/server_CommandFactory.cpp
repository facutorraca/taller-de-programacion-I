#include "server_CommandFactory.h"
#include "server_Command.h"
#include "server_CommandMkd.h"
#include "server_CommandRmd.h"
#include "server_CommandUser.h"
#include "server_CommandList.h"
#include "server_CommandQuit.h"
#include "server_CommandPass.h"
#include "server_CommandUnknown.h"
#include <string>

Command* CommandFactory::create_command() {
    if (this->cmd.compare("LIST") == 0) {
        return new CommandList();
    }
    if (this->cmd.compare("QUIT") == 0) {
        return new CommandQuit();
    }
    if (this->cmd.compare("USER") == 0) {
        return new CommandUser(this->arg);
    }
    if (this->cmd.compare("PASS") == 0) {
        return new CommandPass(this->arg);
    }
    if (this->cmd.compare("MKD") == 0) {
        return new CommandMkd(this->arg);
    }
    if (this->cmd.compare("RMD") == 0) {
        return new CommandRmd(this->arg);
    }
    return new CommandUnknown();
}

void CommandFactory::set_command(std::string cmd) {
    this->cmd.assign(cmd);
}

void CommandFactory::set_argument(std::string arg) {
    this->arg.assign(arg);
}
