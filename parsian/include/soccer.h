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
#include <fstream>

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
    Field field;

    //control
    std::array<double, 10> wheels;
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
    static GameState decideGameState(std::size_t gamestate, bool ballownership);
    static std::string gameStateToString(const GameState &gamestate);
    void updateWorldModel(const aiwc::frame &f);
    void updateField();

    //control
    void set_robot_wheel(std::size_t id, double leftWheel, double rightWheel);
    void set_robot_vel(std::size_t id, double vel_f, double angle,double max_vel);
    void gotopoint(std::size_t id,rcsc::Vector2D pos,double max_vel = 1,double theta = 0);
    void onetouch(std::size_t id,rcsc::Vector2D pos,double theta = 0);
    void kick(int id, const rcsc::Vector2D&  targetPos);
    double th = 10;
    Vector2D lastBehinePos;
    void validatePos(rcsc::Vector2D &targetPos);

    void Goalie(size_t id);

    };


#endif //SOCCER_H
