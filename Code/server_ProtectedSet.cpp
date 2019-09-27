#include "server_ProtectedSet.h"
#include <set>
#include <mutex>
#include <string>
#include <vector>
#include <cstdbool>

bool ProtectedSet::erase(std::string str) {
    std::unique_lock<std::mutex> lock(this->s_mtx);
    size_t erased = this->set.erase(str);
    return erased == 1;
}

bool ProtectedSet::insert(std::string str) {
    std::unique_lock<std::mutex> lock(this->s_mtx);
    std::pair<std::set<std::string>::iterator,bool> ret;
    ret = this->set.insert(str);
    return ret.second; //Bool (inserted/not inserted)
}

void ProtectedSet::get_elements(std::vector<std::string>& buf) {
    std::unique_lock<std::mutex> lock(this->s_mtx);
    std::set<std::string>::iterator iter;
    for (iter = this->set.begin(); iter != this->set.end(); iter++) {
        buf.push_back(*iter);
    }
}
