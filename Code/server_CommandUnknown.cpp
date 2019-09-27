#include "server_CommandUnknown.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

void CommandUnknown::execute(User& user) {
    this->answer.assign("<CommandUnknown>\n");
}

void CommandUnknown::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandUnknown::~CommandUnknown() {}
