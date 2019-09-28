#include "client_ServerProxy.h"
#include "common_Socket.h"
#include <string>
#include <iostream>
#include <cstdbool>

#define ERROR 1
#define SUCCESS 0
#define BEGIN_LIST_CODE "150"
#define END_LIST_CODE "226"
#define QUIT_CODE "221"
#define LEN_FTP_CODE 3

ServerProxy::ServerProxy(const std::string host, const std::string port):
    host(host),
    port(port)
{
    this->connected = false;
}

void ServerProxy::connect() {
    std::string welcome_message;
    this->socket.connect(host, port);
    this->socket.receive(welcome_message);
    std::cout << welcome_message;
    this->connected = true;
}

bool ServerProxy::is_connected() {
    return this->connected;
}

void ServerProxy::receive_list() {
    std::string answer;
    while (answer.substr(0, LEN_FTP_CODE).compare(END_LIST_CODE) != 0) {
        answer.clear();
        if (this->socket.receive(answer) == ERROR) {
            this->connected = false;
            return;
        }
        std::cout << answer;
    }
}

void ServerProxy::execute(const std::string cmd) {
    std::string answer;
    if(this->socket.send(cmd + "\n") == ERROR) {
        this->connected = false;
        return;
    }
    if (this->socket.receive(answer) == ERROR) {
        this->connected = false;
        return;
    }
    std::cout << answer;
    if (answer.substr(0, LEN_FTP_CODE).compare(BEGIN_LIST_CODE) == 0) {
        this->receive_list();
    }
    if (answer.substr(0, LEN_FTP_CODE).compare(QUIT_CODE) == 0) {
        this->connected = false;
    }
}

ServerProxy::~ServerProxy() {}
