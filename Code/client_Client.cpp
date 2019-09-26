#include "client_Client.h"
#include "client_ServerProxy.h"
#include <string>

Client::Client(const std::string host, const std::string port):
    port(port),
    host(host)
{}

void Client::connect() {
    this->server.connect(this->port, this->host);
}

void Client::send(std::string msg) {
    this->server.send(msg);
}

Client::~Client() {}
