//
// Created by parsian-ai on 10/10/19.
//

#include "field.h"

void Field::update(const aiwc::game_info& info) {
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
    this->ourBigPenalty     = Rect2D(ourBigPenaltyA    , ourBigPenaltyC);
    this->ourSmallPenalty   = Rect2D(ourSmallPenaltyA  , ourSmallPenaltyC);
    this->theirBigPenalty   = Rect2D(theirBigPenaltyA  , theirBigPenaltyC);
    this->theirSmallPenalty = Rect2D(theirSmallPenaltyA, theirSmallPenaltyC);

}
