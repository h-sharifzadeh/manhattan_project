#include "soccer.h"

Soccer::Soccer(std::string server_ip, std::size_t port, std::string realm, std::string key, std::string datapath)
        : ai_base(std::move(server_ip), port, std::move(realm), std::move(key), std::move(datapath))
{
    std::cout << "PARSIAN TEAM start" << std::endl;
}

void Soccer::init()
{

}

void Soccer::update(const aiwc::frame &f)
{
    std::cout << "update" << std::endl;
}

void Soccer::finish()
{

}
