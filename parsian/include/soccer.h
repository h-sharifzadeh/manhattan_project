#ifndef SOCCER_H
#define SOCCER_H

#include "ai_base.hpp"

#include <boost/lexical_cast.hpp>

#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "pid.h"
#include "dataStructure.h"

class Soccer: public aiwc::ai_base
{

public:
    Soccer(std::string server_ip, std::size_t port, std::string realm, std::string key, std::string datapath);

    //override functions
    void init() override;
    void update(const aiwc::frame& f) override;
    void finish() override;

//class members
public:
    GameState gameState;
    WorldModel worldModel;
    WorldModel lastWorldModel;

    //control
    std::array<double, 10> wheels;
    PID PID_velN[5];
    PID PID_ang[5];


//class methods
public:
    static GameState decideGameState(std::size_t gamestate, bool ballownership);
    static std::string gameStateToString(const GameState &gamestate);
    void updateWorldModel(const aiwc::frame &f);

    //control
    void set_robot_wheel(std::size_t id, double leftWheel, double rightWheel);
    void set_robot_vel(std::size_t id, double vel_f, double angle);

};


#endif //SOCCER_H
