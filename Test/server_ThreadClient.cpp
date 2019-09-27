#include "server_ThreadClient.h"
#include "common_Socket.h"
#include "server_LogState.h"
#include "server_CommandFactory.h"
#include <cstdbool>
#include <iostream>
#include <string>
#include <thread>


ThreadClient::ThreadClient(Socket socket):
    socket(std::move(socket))
{
    this->alive = true;
}

void ThreadClient::run() {
    this->thread = std::thread(&ThreadClient::communicate, this);
}

void ThreadClient::interpret_command(std::string cmd) {
    if (cmd.length() <= 4) {
        this->cmd_factory.set_command(cmd);
    } else {
        this->cmd_factory.set_command(cmd.substr(0, 4));
        this->cmd_factory.set_argument(cmd.substr(5, std::string::npos));
    }
}

void ThreadClient::communicate() {
    this->socket.send("220 <newClient>\n");

    std::string buf;
    while (this->alive) {
        this->socket.receive(buf);
        this->interpret_command(buf);
        Command* cmd = this->cmd_factory.create_command();
        cmd->execute(user, socket);
        delete cmd;
        buf.clear();
    }
}

ThreadClient::~ThreadClient() {}
