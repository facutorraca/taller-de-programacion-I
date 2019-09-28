#include "server_CommandPwd.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

void CommandPwd::execute(User& user,
                          std::map<std::string, std::string>& config,
                          ProtectedSet& directories) {
    if (user.logged()) {
        this->answer.assign("257 " + config["currentDirectoryMsg"] + "\n");
    } else {
        this->answer.assign("530 " + config["clientNotLogged"] + "\n");
    }
}

void CommandPwd::send_answer(Socket& socket) {
    socket.send(this->answer);
}
