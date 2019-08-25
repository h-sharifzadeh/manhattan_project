#ifndef PARSIAN_DATASTRUCTURE_H
#define PARSIAN_DATASTRUCTURE_H

#include <vector>
#include "geom/vector_2d.h"

using namespace rcsc;

enum class GameState
{
    playOn = 0,
    ourKickOff = 1,
    theirKickOff = 2,
    ourGoalKick = 3,
    theirGoalKick = 4,
    ourCornerKick = 5,
    theirCornerKick = 6,
    ourPenaltyKick = 7,
    theirPenaltyKick = 8
};

struct Robot
{
    Vector2D pos{0, 0};
    Vector2D vel{0, 0};
    std::size_t id{};
    bool active{true};
    double theta{};
    double angularVel{};
};

struct WorldModel
{
    std::array<Robot, 5> ourRobots;
    std::array<Robot, 5> oppRobots;
    Robot ball;
};

#endif //PARSIAN_DATASTRUCTURE_H
