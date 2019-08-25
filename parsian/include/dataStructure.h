#ifndef PARSIAN_DATASTRUCTURE_H
#define PARSIAN_DATASTRUCTURE_H

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

#endif //PARSIAN_DATASTRUCTURE_H
