#include "server_ThreadClient.h"
#include "server_ClientProxy.h"
#include <cstdbool>
#include <iostream>
#include <string>
#include <thread>


ThreadClient::ThreadClient(Socket socket):
    client(std::move(socket))
{
    this->dead = false;
}

void ThreadClient::run() {
    this->thread = std::thread(&ThreadClient::communicate, this);
}

void ThreadClient::communicate() {
    this->client.send_welcome_message();

    while (!this->dead) {
        Command* cmd = this->client.get_command();
        cmd->execute(user);
        this->client.send_command_answer(cmd);
    }
}

ThreadClient::~ThreadClient() {}
