#ifndef _COMMAND_SYST_H_
#define _COMMAND_SYST_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandSyst : public Command {
    std::string answer;

    public:
        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        int send_answer(Socket& socket);
};

#endif
