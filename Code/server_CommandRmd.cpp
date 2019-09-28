#include "server_CommandRmd.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

CommandRmd::CommandRmd(std::string directory):
    directory(directory)
{}

void CommandRmd::execute(User& user,
                          std::map<std::string, std::string>& config,
                          ProtectedSet& directories) {
    if (!user.logged()) {
        this->answer.assign("530 " + config["clientNotLogged"] + "\n");
    }

    if (directories.erase(this->directory)) {
        this->answer.assign("250 " + config["rmdSuccess"] + "\n");
    } else
        this->answer.assign("550 " + config["rmdFailed"] + "\n");
}

int CommandRmd::send_answer(Socket& socket) {
    return socket.send(this->answer);
}

CommandRmd::~CommandRmd() {}
