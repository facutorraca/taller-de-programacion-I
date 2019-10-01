#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

#define PWD "257"
#define HELP "214"
#define QUIT "221"
#define USER "331"
#define UNKW "530"
#define SYST "215"
#define NOT_LOGG "530"
#define MKD_SUCS "257"
#define MKD_FAIL "550"
#define RMD_SUCS "250"
#define RMD_FAIL "550"
#define LIST_BEG "150"
#define LIST_END "226"
#define LOG_SUCS "230"
#define LOG_FAIL "530"

class Command {
    public:
        virtual void execute(User& user,
                             std::map<std::string, std::string>& config,
                             ProtectedSet& directories) = 0;

        virtual void send_answer(Socket& socket) = 0;

        virtual ~Command() {} //Esto esta mal!!
};

#endif
