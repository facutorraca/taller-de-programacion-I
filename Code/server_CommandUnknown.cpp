#include "server_CommandUnknown.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>
#include <map>

void CommandUnknown::execute(User& user,
                             std::map<std::string, std::string>& config) {
    if (user.is_logged()) {
        this->answer.assign(config["unknownCommand"] + "\n");
    } else {
        this->answer.assign(config["clientNotLogged"] + "\n");
    }

}

void CommandUnknown::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandUnknown::~CommandUnknown() {}
