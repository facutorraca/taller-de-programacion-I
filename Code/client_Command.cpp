#include "client_ServerProxy.h"
#include "client_Commnad.h"
#include <string>
#include <iostream>

Commnad::Commnad(std::string cmd):
    cmd(cmd)
{}

void Commnad::execute(ServerProxy& server) {
    server.execute(this->inst);
}

Commnad::~Commnad() {}
