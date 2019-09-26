#include "client_CommandUser.h"
#include "client_Command.h"
#include <string>

CommandUser::CommandUser(std::string args):
    Command("USER " + args + "\n")
{}

CommandUser::~CommandUser() {}
