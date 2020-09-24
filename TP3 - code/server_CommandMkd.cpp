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
        this->answer.assign(std::string(NOT_LOGG) + " " +
                            config["clientNotLogged"] + "\n");
        return;
    }

    if (directories.insert(this->directory)) {
        this->answer.assign(std::string(MKD_SUCS) +
                            " \"" + this->directory + "\" " +
                            config["mkdSuccess"] + "\n");
    } else {
        this->answer.assign(std::string(MKD_FAIL) + " " +
                            config["mkdFailed"] + "\n");
    }
}

void CommandMkd::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandMkd::~CommandMkd() {}
