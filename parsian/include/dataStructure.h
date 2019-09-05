#ifndef PARSIAN_DATASTRUCTURE_H
#define PARSIAN_DATASTRUCTURE_H

#include <vector>
#include "geom/vector_2d.h"
#include "geom/rect_2d.h"

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

struct Field
{
    Vector2D cornerA;
    Vector2D cornerB;
    Vector2D cornerC;
    Vector2D cornerD;
    Vector2D ourGoalCenter;
    Vector2D ourBigPenaltyA;
    Vector2D ourBigPenaltyB;
    Vector2D ourBigPenaltyC;
    Vector2D ourBigPenaltyD;
    Vector2D ourSmallPenaltyA;
    Vector2D ourSmallPenaltyB;
    Vector2D ourSmallPenaltyC;
    Vector2D ourSmallPenaltyD;
    Vector2D ourGoalU;
    Vector2D ourGoalD;
    Vector2D center;
    Vector2D theirGoalCenter;
    Vector2D theirBigPenaltyA;
    Vector2D theirBigPenaltyB;
    Vector2D theirBigPenaltyC;
    Vector2D theirBigPenaltyD;
    Vector2D theirSmallPenaltyA;
    Vector2D theirSmallPenaltyB;
    Vector2D theirSmallPenaltyC;
    Vector2D theirSmallPenaltyD;
    Vector2D theirGoalU;
    Vector2D theirGoalD;

    Rect2D ourBigPenalty;
    Rect2D ourSmallPenalty;
    Rect2D theirBigPenalty;
    Rect2D theirSmallPenalty;

};

#endif //PARSIAN_DATASTRUCTURE_H
