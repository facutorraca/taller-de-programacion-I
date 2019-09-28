#include "server_CommandSyst.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

void CommandSyst::execute(User& user,
                          std::map<std::string, std::string>& config,
                          ProtectedSet& directories) {
    if (user.logged()) {
        this->answer.assign("215 " + config["systemInfo"] + "\n");
    } else {
        this->answer.assign("530 " + config["clientNotLogged"] + "\n");
    }
}

int CommandPass::send_answer(Socket& socket) {
    return socket.send(this->answer);
}
