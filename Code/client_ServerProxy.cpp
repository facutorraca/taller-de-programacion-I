#include "client_ServerProxy.h"

ServerProxy::ServerProxy(const std::string host, const std::string port) {
    this->c_socket.connect(port, host);
}

ServerProxy::execute(std::string msg) {
    this->c_socket.send(msg);
}

ServerProxy::~ServerProxy() {}
