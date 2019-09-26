#include "client_ServerProxy.h"

ServerProxy::ServerProxy() {}

void ServerProxy::connect(const std::string host, const std::string port) {
    this->c_socket.connect(port, host);
}

void ServerProxy::send(std::string msg) {
    this->c_socket.send(msg);
}

ServerProxy::~ServerProxy() {}
