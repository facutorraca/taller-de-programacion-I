#include "server_CommandUser.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

CommandUser::CommandUser(std::string username):
    username(username)
{}

void CommandUser::execute(User& user, Socket& socket) {
    user.set_username(this->username);
    socket.send("331 <passRequired>\n");
}

CommandUser::~CommandUser() {}
