#include "client_PassInstruction.h"
#include "client_Instruction.h"
#include <string>

PassInstruction::PassInstruction(std::string args):
    Instruction("PASS " + args + "\n")
{}

PassInstruction::~PassInstruction() {}
