#include "server_CommandMkd.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

CommandMkd::CommandMkd(std::string directory):
    directory(directory)
{}

void CommandMkd::execute(User& user,
                         std::map<std::string, std::string>& config,
                         ProtectedSet& directories) {

    if (!user.logged()) {
        this->answer.assign("530 " + config["clientNotLogged"] + "\n");
        return;
    } else {
        if (directories.insert(this->directory)) {
            this->answer.assign("257 " + this->directory + " " +
                                config["mkdSuccess"] + "\n");
        } else {
            this->answer.assign("550 " + config["mkdFailed"] + "\n");
        }
    }
}

int CommandMkd::send_answer(Socket& socket) {
    return socket.send(this->answer);
}

CommandMkd::~CommandMkd() {}
