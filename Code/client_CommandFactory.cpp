#include "client_CommandFactory.h"
#include "client_CommandRmd.h"
#include "client_CommandPwd.h"
#include "client_CommandMkd.h"
#include "client_CommandUser.h"
#include "client_CommandPass.h"
#include "client_CommandSyst.h"
#include "client_CommandList.h"
#include "client_CommandHelp.h"
#include <iostream>
#include <string>

CommnadFactory::CommnadFactory() {}

void CommnadFactory::set_argument(std::string arg) {
    this->arg = arg;
}

void CommnadFactory::set_commnad(std::string cmd) {
    this->cmd = cmd;
}

Command CommnadFactory::create_command() {
    if (this->cmd.compare("USER") == 0) {
        return CommandUser(this->arg);
    } else if (this->cmd.compare("PASS") == 0) {
        return CommandPass(this->arg);
    } else if (this->cmd.compare("SYST") == 0) {
        return CommandSyst();
    } else if (this->cmd.compare("LIST") == 0) {
        return CommandList();
    } else if (this->cmd.compare("HELP") == 0) {
        return CommnadHelp();
    } else if (this->cmd.compare("PWD") == 0) {
        return CommnadPwd();
    } else if (this->cmd.compare("MKD") == 0) {
        return CommnadMkd();
    } else { //(this->cmd.compare("RMD") == 0) {
        return CommnadRmd();
    }
}

CommnadFactory::~CommnadFactory() {}
