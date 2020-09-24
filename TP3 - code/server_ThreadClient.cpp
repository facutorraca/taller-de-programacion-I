#include "server_ThreadClient.h"
#include "server_ClientProxy.h"
#include "server_ProtectedSet.h"
#include <cstdbool>
#include <iostream>
#include <string>
#include <thread>
#include <map>

#define ERROR 1
#define SUCCESS 0

ThreadClient::ThreadClient(Socket socket,
                           std::map<std::string, std::string>& config,
                           ProtectedSet& directories):
    client(std::move(socket)),
    user(config["user"], config["password"]),
    directories(directories),
    config(config)
{
    this->dead = false;
}

void ThreadClient::stop() {
    this->client.disconnect();
    this->dead = true;
}

void ThreadClient::run() {
    if (this->client.send_welcome_message(this->config["newClient"]) == ERROR) {
        this->dead = true;
    }

    while (!this->dead) {
        Command* command = this->client.get_command();
        if (command) {
            command->execute(user, this->config, this->directories);
            if (this->client.send_command_answer(command) == SUCCESS) {
                this->dead = true; //Connection interrupted during send
            }
            this->dead = this->user.logged_out();
        } else {
            this->dead = true;///Connection interrupted during recv
        }
    }
}

bool ThreadClient::is_dead() {
    return this->dead;
}

ThreadClient::~ThreadClient() {}
