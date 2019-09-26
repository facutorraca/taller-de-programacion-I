#include "client_CommandList.h"
#include "client_Command.h"
#include <string>

CommandList::CommandList():
    Command("LIST\n")
{}

CommandList::~CommandList() {}
