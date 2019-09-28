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
        this->answer.assign("214 " + config["clientNotLogged"] + "\n");
    }
}

int CommandPwd::send_answer(Socket& socket) {
    return socket.send(this->answer);
}
