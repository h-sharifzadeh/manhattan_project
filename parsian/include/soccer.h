#include "ai_base.hpp"

#include <boost/lexical_cast.hpp>

#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>


class Soccer: public aiwc::ai_base
{

public:
    Soccer(std::string server_ip, std::size_t port, std::string realm, std::string key, std::string datapath);

    //override functions
    void init() override;
    void update(const aiwc::frame& f) override;
    void finish() override;


};


