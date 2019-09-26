#include "client_CommandPass.h"
#include "client_Command.h"
#include <string>

CommandPass::CommandPass(std::string args):
    Command("PASS " + args + "\n")
{}

CommandPass::~CommandPass() {}
