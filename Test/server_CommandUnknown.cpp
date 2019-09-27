#include "server_CommandUnknown.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

void CommandUnknown::execute(User& user, Socket& socket) {
    socket.send("230 <unknownCommand>\n");
}

CommandUnknown::~CommandUnknown() {}
