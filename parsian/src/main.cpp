#include <iostream>
#include "soccer.h"

int main(int argc, char *argv[])
{
    if(argc < 6) {
        std::cerr << "Usage " << argv[0] << " server_ip port realm key datapath" << std::endl;
        return -1;
    }

    const auto& server_ip = std::string(argv[1]);
    const auto& port      = boost::lexical_cast<std::size_t>(argv[2]);
    const auto& realm     = std::string(argv[3]);
    const auto& key       = std::string(argv[4]);
    const auto& datapath  = std::string(argv[5]);

    Soccer ai(server_ip, port, realm, key, datapath);

    ai.run();

    return 0;
}