#include "client_ServerProxy.h"
#include "common_Socket.h"
#include <iostream>
#include <string>

ServerProxy::ServerProxy(const std::string host, const std::string port):
    host(host),
    port(port)
{}

void ServerProxy::connect() {
    std::string welcome_message;
    this->socket.connect(host, port);
    this->socket.receive(welcome_message);
    std::cout << welcome_message;
}

void ServerProxy::execute(const std::string cmd) {
    std::string answer;
    this->socket.send(cmd);
    this->socket.receive(answer);
    std::cout << answer;
}

ServerProxy::~ServerProxy() {}
