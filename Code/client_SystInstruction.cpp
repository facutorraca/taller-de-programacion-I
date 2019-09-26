#include "client_SystInstruction.h"
#include "client_Instruction.h"
#include <string>

SystInstruction::SystInstruction():
    Instruction("SYST\n")
{}

SystInstruction::~SystInstruction() {}
