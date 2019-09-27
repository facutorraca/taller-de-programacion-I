#include "client_ServerProxy.h"
#include "common_Socket.h"
#include <iostream>
#include <string>

#define BEGIN_LIST_CODE "150"
#define END_LIST_CODE "226"

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
    this->socket.send(cmd + "\n");
    this->socket.receive(answer);
    std::cout << answer;
    if (answer.substr(0,3).compare(BEGIN_LIST_CODE) == 0) {
        while (answer.substr(0,3).compare(END_LIST_CODE) != 0) {
            answer.clear();
            this->socket.receive(answer);
            std::cout << answer;
        }
    }
}

ServerProxy::~ServerProxy() {}
