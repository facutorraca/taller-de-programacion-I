#include "client_UserInstruction.h"
#include "client_Instruction.h"
#include <string>

UserInstruction::UserInstruction(std::string args):
    Instruction("USER " + args + "\n")
{}

UserInstruction::~UserInstruction() {}
