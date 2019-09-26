#include "client_ServerProxy.h"
#include <iostream>

ServerProxy::ServerProxy(const std::string host, const std::string port) {
    this->c_socket.connect(host, port);
}

void ServerProxy::execute(std::string cmd) {
    this->c_socket.send(cmd);
}

ServerProxy::~ServerProxy() {}
