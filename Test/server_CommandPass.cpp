#include "server_CommandPass.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

CommandPass::CommandPass(std::string password):
    password(password)
{}

void CommandPass::execute(User& user, Socket& socket) {
    user.set_password(this->password);
    if (user.verify_login()) {
        socket.send("230 <loginSuccess>\n");
    } else
        socket.send("530 <loginFailed>\n");
}

CommandPass::~CommandPass() {}
