#ifndef DELFT_SOCCER_FIELD_H
#define DELFT_SOCCER_FIELD_H

#include "ai_base.hpp"

#include <vector_2d.h>
#include <rect_2d.h>

using namespace rcsc;


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
	
	void update(const aiwc::game_info& info);
	
};

void Field::update(const aiwc::game_info& info) {
	
	this->ourBigPenalty     = Rect2D(ourBigPenaltyA    , ourBigPenaltyC);
	this->ourSmallPenalty   = Rect2D(ourSmallPenaltyA  , ourSmallPenaltyC);
	this->theirBigPenalty   = Rect2D(theirBigPenaltyA  , theirBigPenaltyC);
	this->theirSmallPenalty = Rect2D(theirSmallPenaltyA, theirSmallPenaltyC);
	
	this->cornerA = {(0 - info.field[0]*0.5), (0 - info.field[1]*0.5)};
	this->cornerB = {(0 + info.field[0]*0.5), (0 - info.field[1]*0.5)};
	this->cornerC = {(0 + info.field[0]*0.5), (0 + info.field[1]*0.5)};
	this->cornerD = {(0 - info.field[0]*0.5), (0 + info.field[1]*0.5)};
	this->ourGoalCenter = {(0 - info.field[0]*0.5), 0};
	this->ourBigPenaltyA = ourGoalCenter + Vector2D{0, -info.penalty_area[1]*0.5};
	this->ourBigPenaltyB = ourGoalCenter + Vector2D{info.penalty_area[0], -info.penalty_area[1]*0.5};
	this->ourBigPenaltyC = ourGoalCenter + Vector2D{info.penalty_area[0], +info.penalty_area[1]*0.5};
	this->ourBigPenaltyD = ourGoalCenter + Vector2D{0, +info.penalty_area[1]*0.5};
	this->ourSmallPenaltyA = ourGoalCenter + Vector2D{0, -info.goal_area[1]*0.5};
	this->ourSmallPenaltyB = ourGoalCenter + Vector2D{info.goal_area[0], -info.goal_area[1]*0.5};
	this->ourSmallPenaltyC = ourGoalCenter + Vector2D{info.goal_area[0], +info.goal_area[1]*0.5};
	this->ourSmallPenaltyD = ourGoalCenter + Vector2D{0, +info.goal_area[1]*0.5};
	this->ourGoalU = ourGoalCenter + Vector2D{0, -info.goal[1]*0.5};
	this->ourGoalD = ourGoalCenter + Vector2D{0, +info.goal[1]*0.5};
	this->center = {0, 0};
	this->theirGoalCenter = {(0 + info.field[0]*0.5), 0};
	this->theirBigPenaltyA = theirGoalCenter + Vector2D{-info.penalty_area[0], -info.penalty_area[1]*0.5};
	this->theirBigPenaltyB = theirGoalCenter + Vector2D{0, -info.penalty_area[1]*0.5};
	this->theirBigPenaltyC = theirGoalCenter + Vector2D{0, +info.penalty_area[1]*0.5};
	this->theirBigPenaltyD = theirGoalCenter + Vector2D{-info.penalty_area[0], +info.penalty_area[1]*0.5};
	this->theirSmallPenaltyA = theirGoalCenter + Vector2D{-info.goal_area[0], -info.goal_area[1]*0.5};
	this->theirSmallPenaltyB = theirGoalCenter + Vector2D{0, -info.goal_area[1]*0.5};
	this->theirSmallPenaltyC = theirGoalCenter + Vector2D{0, +info.goal_area[1]*0.5};
	this->theirSmallPenaltyD = theirGoalCenter + Vector2D{-info.goal_area[0], +info.goal_area[1]*0.5};
	this->theirGoalU = theirGoalCenter + Vector2D{0, -info.goal[1]*0.5};
	this->theirGoalD = theirGoalCenter + Vector2D{0, +info.goal[1]*0.5};
	
}

#endif //DELFT_SOCCER_FIELD_H
