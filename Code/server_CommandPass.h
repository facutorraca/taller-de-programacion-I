#ifndef _COMMAND_PASS_H_
#define _COMMAND_PASS_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

class CommandPass : public Command {
    std::string answer;
    std::string password;

    public:
        CommandPass(std::string password);

        void send_answer(Socket& socket);

        void execute(User& user);

        ~CommandPass();
};

#endif
