#include "client_ServerProxy.h"
#include "client_Command.h"
#include <string>
#include <iostream>

Command::Command(std::string cmd):
    cmd(cmd)
{}

void Command::execute(ServerProxy& server) {
    server.execute(this->cmd);
}

Command::~Command() {}
