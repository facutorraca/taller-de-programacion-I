#include "client_ServerProxy.h"
#include "client_Instruction.h"
#include <string>
#include <iostream>

Instruction::Instruction(std::string inst):
    inst(inst)
{}

void Instruction::send(ServerProxy* server) {
    server->send(this->inst);
}

Instruction::~Instruction() {}
