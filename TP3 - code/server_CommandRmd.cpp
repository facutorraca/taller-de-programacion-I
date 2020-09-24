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
        this->answer.assign(std::string(NOT_LOGG) + " " +
                            config["clientNotLogged"] + "\n");
    }

    if (directories.erase(this->directory)) {
        this->answer.assign(std::string(RMD_SUCS) +
                            " \"" + this->directory + "\" " +
                            config["rmdSuccess"] + "\n");
    } else {
        this->answer.assign(std::string(RMD_FAIL) + " " +
                            config["rmdFailed"] + "\n");
    }
}

void CommandRmd::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandRmd::~CommandRmd() {}
