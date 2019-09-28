#include "server_CommandList.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <vector>
#include <map>

#define ERROR 1
#define SUCCESS 0

CommandList::CommandList() {}

void CommandList::execute(User& user,
                         std::map<std::string, std::string>& config,
                         ProtectedSet& directories) {

    if (!user.logged()) {
        this->answers.push_back("530 " + config["clientNotLogged"] + "\n");
        return;
    }

    this->answers.push_back("150 " + config["listBegin"] + "\n");

    std::vector<std::string> dirs;
    directories.get_elements(dirs);

    for (size_t i = 0; i < dirs.size(); i++) {
        this->answers.push_back("drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 "
                                + dirs[i] + "\n");
    }

    this->answers.push_back("226 " + config["listEnd"] + "\n");
}

void CommandList::send_answer(Socket& socket) {
    for (size_t i = 0; i < this->answers.size(); i++) {
        socket.send(this->answers[i]);
    }
}

CommandList::~CommandList() {}
