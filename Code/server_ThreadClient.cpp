#include "server_ThreadClient.h"
#include "server_ClientProxy.h"
#include "server_ProtectedSet.h"
#include <cstdbool>
#include <iostream>
#include <string>
#include <thread>



ThreadClient::ThreadClient(Socket socket,
                           std::map<std::string, std::string>& config,
                           ProtectedSet& directories):
    user(config["user"], config["password"]),
    client(std::move(socket)),
    directories(directories),
    config(config)
{
    this->dead = false;
}

void ThreadClient::run() {
    this->thread = std::thread(&ThreadClient::communicate, this);
}

void ThreadClient::join() {
    this->thread.join();
}

void ThreadClient::stop() {
    this->client.disconnect();
    this->dead = true;
}

void ThreadClient::communicate() {
    this->client.send_welcome_message(this->config["newClient"]);

    while (!this->dead) {
        Command* command = this->client.get_command();
        command->execute(user, this->config, this->directories);
        this->client.send_command_answer(command);
        this->dead = this->user.logged_out();
    }
}

bool ThreadClient::is_dead() {
    return this->dead;
}

ThreadClient::~ThreadClient() {}
