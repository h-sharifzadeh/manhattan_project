//
// Created by parsian-ai on 9/14/19.
//

#ifndef PARSIAN_DEFENCE_H
#define PARSIAN_DEFENCE_H

void Soccer::Defence(std::vector<size_t> ids) {
    Circle2D defence_line(field.ourGoalCenter, 1);
    Segment2D ball_to_goal(field.ourGoalCenter, worldModel.ball.pos);
    Vector2D sol1, sol2;
    if (defence_line.intersection(ball_to_goal, &sol1, &sol2)) {
        for (int i = 0; i < ids.size(); ++i) {
            gotopoint(ids[i], sol1 + (Vector2D(0, i * 2 - 3) * i * .1));
        }
    } else
        for (int i = 0; i < ids.size(); ++i) {

            double theta = 180.0 / (ids.size() + 1) * (i + 1);
            double x = sin(theta);
            double y = cos(theta);
            gotopoint(ids[i], field.ourGoalCenter + Vector2D(x, y));
        }
}

#endif //PARSIAN_DEFENCE_H
