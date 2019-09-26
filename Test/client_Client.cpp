#include "client_Client.h"
#include "client_ServerProxy.h"
#include <string>
#include <iostream>

Client::Client(const std::string host, const std::string port):
    server(host, port) {}

void Client::read_input(std::string& cmd) {
    cmd.clear();
    std::getline(std::cin, cmd);
    cmd.append("\n");
}

void Client::run() {
    this->server.connect();
    
    std::string cmd;
    while (true) {
        this->read_input(cmd);
        server.execute(cmd);
    }
}

Client::~Client() {}
