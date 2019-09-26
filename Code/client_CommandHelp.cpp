#include "client_CommandHelp.h"
#include "client_Command.h"
#include <string>

CommandHelp::CommandHelp():
    Command("HELP\n")
{}

CommandHelp::~CommandHelp() {}
