#include "client_CommandSyst.h"
#include "client_Command.h"
#include <string>

CommandSyst::CommandSyst():
    Command("SYST\n")
{}

CommandSyst::~CommandSyst() {}
