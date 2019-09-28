#include "server_CommandHelp.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

void CommandHelp::execute(User& user,
                          std::map<std::string, std::string>& config,
                          ProtectedSet& directories) {
    if (user.logged()) {
        this->answer.assign("215 " + config["commands"] + "\n");
    } else {
        this->answer.assign("214 " + config["clientNotLogged"] + "\n");
    }
}

int CommandHelp::send_answer(Socket& socket) {
    return socket.send(this->answer);
}
