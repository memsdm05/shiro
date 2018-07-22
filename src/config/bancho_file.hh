#ifndef SHIRO_BANCHO_FILE_HH
#define SHIRO_BANCHO_FILE_HH

#include <string>

namespace shiro::config::bancho {

    extern std::string host;
    extern int port;
    extern uint16_t concurrency;

    void parse();

}

#endif //SHIRO_BANCHO_FILE_HH
