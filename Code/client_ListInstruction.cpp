#include "client_ListInstruction.h"
#include "client_Instruction.h"
#include <string>

ListInstruction::ListInstruction():
    Instruction("LIST\n")
{}

ListInstruction::~ListInstruction() {}
