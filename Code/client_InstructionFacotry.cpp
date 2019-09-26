#include "client_InstructionFactory.h"
#include "client_RmdInstruction.h"
#include "client_UserInstruction.h"
#include "client_PassInstruction.h"
#include <string>
#include <iostream>

InstructionFactory::InstructionFactory() {}

void InstructionFactory::set_args(std::string args) {
    this->args = args;
}

void InstructionFactory::set_instruction(std::string inst) {
    this->inst = inst;
}

Instruction InstructionFactory::create_instruction() {
    if (this->inst.compare("USER") == 0) {
        return UserInstruction(this->args);
    } else if (this->inst.compare("PASS") == 0) {
        return PassInstruction(this->args);
    } /* else if (this->inst.compare("SYST") == 0) {
        return std::move(SystInstruction inst());
    } else if (this->inst.compare("LIST") == 0) {
        return std::move(HelpInstruction inst());
    } else if (this->inst.compare("HELP") == 0) {
        return std::move(PwdrInstruction inst());
    } else if (this->inst.compare("PWD") == 0) {
        return std::move(UserInstruction inst());
    } else if (this->inst.compare("MKD") == 0) {
        return std::move(MkdInstruction inst()); }*/
    else { //(this->inst.compare("RMD") == 0) {
        return RmdInstruction();
    }
}

InstructionFactory::~InstructionFactory() {}
