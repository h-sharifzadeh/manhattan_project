#ifndef SOCCER_H
#define SOCCER_H


#include "pid.h"
#include "ai_base.hpp"
#include "field.h"
#include "gamestate.h"
#include "worldmodel.h"

#include <boost/lexical_cast.hpp>

#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>

class Soccer : public aiwc::ai_base
{

public:
    Soccer(const std::string& server_ip, std::size_t port, const std::string& realm, std::string key, std::string datapath);

    //override functions
    void init() override;
    void update(const aiwc::frame& f) override;
    void finish() override;

//class members
public:
    WorldModel* wm;
    WorldModel* lwm;
    Field field;

    //control
    std::array<double, 10> wheels{};
    PID PID_velN[5];
    PID PID_ang[5];
    PID PID_pos[5];
    enum STATE {
        AVOID = 0,
        BEHIND = 1,
        KICK = 2
    }state;
//class methods
public:
    void updateWorldModel(const aiwc::frame &f);
    void updateField();

    //control
    void setWheels(int id, double leftWheel, double rightWheel);
    void setWheelsPID(int id, double vel, double w);
    void setVel(int id, double vel_f, double angle, double max_vel);
    void move(int id, rcsc::Vector2D pos, double max_vel = 2.5, double theta = 0);
    void fast(int id, rcsc::Vector2D pos, double theta = 0);
    void kick(int id, const rcsc::Vector2D&  targetPos);
    int attack_state{} ;

    void GK(int id);
    void defense(std::vector<int> ids);
    void attacker(int id);
    void coach();

};


#endif //SOCCER_H
