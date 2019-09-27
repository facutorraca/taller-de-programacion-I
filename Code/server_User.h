#ifndef _USER_H_
#define _USER_H_

#include "common_Socket.h"
#include "server_LogState.h"
#include <string>
#include <cstdbool>

class User {
    log_state_t log_state;
    std::string username;
    std::string password;

    public:
        User();

        bool verify_login();

        bool is_logged();

        void set_username(std::string username);

        void set_password(std::string password);

        ~User();
};

#endif
