#include "server_ClientProxy.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_CommandFactory.h"
#include <string>

#define LEN_INST_NO_ARGS 4

ClientProxy::ClientProxy(Socket socket):
    socket(std::move(socket))
{}

void ClientProxy::send_welcome_message(std::string msg) {
    this->socket.send("220 " + msg + "\n");
}

void ClientProxy::interpret_command(std::string cmd) {
    if (cmd.length() <= LEN_INST_NO_ARGS) {
        this->cmd_factory.set_command(cmd);
    } else {
        size_t pos_delim = cmd.find(' ');
        this->cmd_factory.set_command(cmd.substr(0, pos_delim));
        this->cmd_factory.set_argument(cmd.substr(pos_delim + 1,
                                                  std::string::npos));
    }
}

Command* ClientProxy::get_command() {
    std::string cmd;
    this->socket.receive(cmd);
    cmd.pop_back(); //Pop EOL
    this->interpret_command(cmd);
    return this->cmd_factory.create_command();
}

void ClientProxy::send_command_answer(Command* command) {
    command->send_answer(this->socket);
    delete command;
}

ClientProxy::~ClientProxy() {}
