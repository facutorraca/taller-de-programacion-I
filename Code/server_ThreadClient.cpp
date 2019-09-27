#include "server_ThreadClient.h"
#include "server_ClientProxy.h"
#include <cstdbool>
#include <iostream>
#include <string>
#include <thread>



ThreadClient::ThreadClient(Socket socket,
                           std::map<std::string, std::string>& config):
    client(std::move(socket)),
    config(config)
{
    this->dead = false;
}

void ThreadClient::run() {
    this->thread = std::thread(&ThreadClient::communicate, this);
}

void ThreadClient::communicate() {
    this->client.send_welcome_message(this->config["newClient"]);

    while (!this->dead) {
        Command* command = this->client.get_command();
        command->execute(user, this->config);
        this->client.send_command_answer(command);
    }
}

ThreadClient::~ThreadClient() {}
