#ifndef _COMMAND_USER_H_
#define _COMMAND_USER_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

class CommandUser : public Command {
    std::string answer;
    std::string username;

    public:
        CommandUser(std::string username);

        void send_answer(Socket& socket);

        void execute(User& user);

        ~CommandUser();
};

#endif
