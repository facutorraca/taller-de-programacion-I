#include "server_CommandPass.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

CommandPass::CommandPass(std::string password):
    password(password)
{}

void CommandPass::execute(User& user,
                          std::map<std::string, std::string>& config,
                          ProtectedSet& directories) {
    user.set_password(this->password);
    if (user.verify_login()) {
        this->answer.assign("230 " + config["loginSuccess"] + "\n");
    } else
        this->answer.assign("530 " + config["loginFailed"] + "\n");
}

void CommandPass::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandPass::~CommandPass() {}
