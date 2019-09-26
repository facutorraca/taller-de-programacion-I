#include "client_InstructionFactory.h"
#include "client_RmdInstruction.h"
#include "client_PwdInstruction.h"
#include "client_MkdInstruction.h"
#include "client_UserInstruction.h"
#include "client_PassInstruction.h"
#include "client_SystInstruction.h"
#include "client_ListInstruction.h"
#include "client_HelpInstruction.h"
#include <iostream>
#include <string>

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
    } else if (this->inst.compare("SYST") == 0) {
        return SystInstruction();
    } else if (this->inst.compare("LIST") == 0) {
        return ListInstruction();
    } else if (this->inst.compare("HELP") == 0) {
        return HelpInstruction();
    } else if (this->inst.compare("PWD") == 0) {
        return PwdInstruction();
    } else if (this->inst.compare("MKD") == 0) {
        return MkdInstruction();
    } else { //(this->inst.compare("RMD") == 0) {
        return RmdInstruction();
    }
}

InstructionFactory::~InstructionFactory() {}
