#include "server_CommandPass.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

CommandPass::CommandPass(std::string password):
    password(password)
{}

void CommandPass::execute(User& user) {
    user.set_password(this->password);
    if (user.verify_login()) {
        this->answer.assign("230 <loginSuccess>\n");
    } else
        this->answer.assign("530 <loginFailed>\n");
}

void CommandPass::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandPass::~CommandPass() {}
