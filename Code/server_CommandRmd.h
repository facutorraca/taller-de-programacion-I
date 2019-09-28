#ifndef _COMMAND_RMD_H_
#define _COMMAND_RMD_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandRmd : public Command {
    std::string answer;
    std::string directory;

    public:
        CommandRmd(std::string directory);

        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        int send_answer(Socket& socket);

        ~CommandRmd();
};

#endif
