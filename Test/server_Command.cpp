#include "server_Command.h"
#include <string>
#include <iostream>

Command::Command(std::string cmd):
    cmd(cmd)
{}

void Command::execute() {

}

Command::~Command() {}
