#include "server_ProtectedSet.h"
#include <set>
#include <string>
#include <cstdbool>

bool ProtectedSet::find(std::string str) {
    return true;
}

bool ProtectedSet::erase(std::string str) {
    size_t erased = this->set.erase(str);
    return erased == 1;
}

bool ProtectedSet::insert(std::string str) {
    std::pair<std::set<std::string>::iterator,bool> ret;
    ret = this->set.insert(str);
    return ret.second; //Bool (inserted/not inserted)
}
