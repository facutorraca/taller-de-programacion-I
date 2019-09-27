#include "client_Client.h"
#include "client_ServerProxy.h"
#include <string>
#include <iostream>

Client::Client(const std::string host, const std::string port):
    server(host, port) {}

void Client::start() {
    this->server.connect();

    std::string cmd;
    while (this->server.is_connected() && std::getline(std::cin, cmd)) {
        this->server.execute(cmd);
        cmd.clear();
    }
}

Client::~Client() {}
