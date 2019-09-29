#include "server_ClientProxy.h"
#include "common_SocketError.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_CommandFactory.h"
#include <iostream>
#include <string>

#define ERROR 1
#define SUCCESS 0
#define LEN_INST_NO_ARGS 4

ClientProxy::ClientProxy(Socket socket):
    socket(std::move(socket))
{}

int ClientProxy::send_welcome_message(std::string msg) {
    try {
        this->socket.send("220 " + msg + "\n");
        return SUCCESS;
    } catch (const SocketError& exception) {
        std::cerr << exception.what() << " -> Client was closed" << '\n';
        this->disconnect();
        return ERROR;
    }
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

void ClientProxy::disconnect() {
    this->socket.close();
}

Command* ClientProxy::get_command() {
    try {
        std::string cmd;
        this->socket.receive(cmd);
        cmd.pop_back(); //Pop EOL
        this->interpret_command(cmd);
        return this->cmd_factory.create_command();
    } catch (const SocketError& exception) {
        std::cerr << exception.what() << " -> Client was closed" << '\n';
        this->disconnect();
        return nullptr;
    }

}

int ClientProxy::send_command_answer(Command* command) {
    try {
        command->send_answer(this->socket);
        delete command;
        return SUCCESS;
    } catch (const SocketError& exception) {
        std::cerr << exception.what() << " -> Client was closed" << '\n';
        this->disconnect();
        delete command;
        return ERROR;
    }
}

ClientProxy::~ClientProxy() {}
