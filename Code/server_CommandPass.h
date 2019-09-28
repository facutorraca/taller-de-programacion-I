#ifndef _COMMAND_PASS_H_
#define _COMMAND_PASS_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandPass : public Command {
    std::string answer;
    std::string password;

    public:
        CommandPass(std::string password);

        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        int send_answer(Socket& socket);

        ~CommandPass();
};

#endif
