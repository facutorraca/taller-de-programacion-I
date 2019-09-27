#include "server_User.h"
#include "common_Socket.h"
#include "server_LogState.h"
#include <string>
#include <cstdbool>

User::User() {
    this->log_state = NotConnected;
}

void User::set_username(std::string username) {
    this->username.assign(username);
    this->log_state = NoPassword;
}

void User::set_password(std::string password) {
    this->password.assign(password);
}

bool User::verify_login() {
    this->log_state = Connected;
    return true;
}

User::~User() {}
