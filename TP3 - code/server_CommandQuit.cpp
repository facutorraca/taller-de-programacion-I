#include "server_CommandQuit.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

CommandQuit::CommandQuit() {}

void CommandQuit::execute(User& user,
                          std::map<std::string, std::string>& config,
                          ProtectedSet& directories) {
    user.log_out();
    this->answer.assign(std::string(QUIT) + " " +
                        config["quitSuccess"] + "\n");
}

void CommandQuit::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandQuit::~CommandQuit() {}
