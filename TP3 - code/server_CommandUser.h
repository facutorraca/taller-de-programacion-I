#ifndef _COMMAND_USER_H_
#define _COMMAND_USER_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandUser : public Command {
    std::string answer;
    std::string username;

    public:
        explicit CommandUser(std::string username);

        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        void send_answer(Socket& socket);

        ~CommandUser();
};

#endif
