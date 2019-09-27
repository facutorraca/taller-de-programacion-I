#include "client_Client.h"
#include "client_ServerProxy.h"
#include <string>
#include <iostream>

Client::Client(const std::string host, const std::string port):
    server(host, port) {}

void Client::start() {
    this->server.connect();

    std::string cmd;
    while (std::getline(std::cin, cmd) && this->server.is_connected()) {
        this->server.execute(cmd);
        cmd.clear();
    }
}

Client::~Client() {}
