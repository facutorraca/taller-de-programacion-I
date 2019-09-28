#include "server_CommandUnknown.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

void CommandUnknown::execute(User& user,
                             std::map<std::string, std::string>& config,
                             ProtectedSet& directories) {
    if (user.logged()) {
        this->answer.assign("500 " + config["unknownCommand"] + "\n");
    } else {
        this->answer.assign("530 " + config["clientNotLogged"] + "\n");
    }

}

int CommandUnknown::send_answer(Socket& socket) {
    return socket.send(this->answer);
}

CommandUnknown::~CommandUnknown() {}
