#ifndef DELFT_SOCCER_FIELD_H
#define DELFT_SOCCER_FIELD_H

#include "ai_base.hpp"

#include <vector_2d.h>
#include <rect_2d.h>

using namespace rcsc;


class Field
{
public:
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
	
	void update(const aiwc::game_info& info);
	
};
#endif //DELFT_SOCCER_FIELD_H
