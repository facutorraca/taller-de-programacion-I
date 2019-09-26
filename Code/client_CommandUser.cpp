#include "client_CommandUser.h"
#include "client_Instruction.h"
#include <string>

CommandUser::CommandUser(std::string args):
    Command("USER " + args + "\n")
{}

CommandUser::~CommandUser() {}
