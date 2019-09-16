//
// Created by parsian-ai on 9/14/19.
//

#ifndef PARSIAN_DEFENCE_H
#define PARSIAN_DEFENCE_H

void Soccer::Defence(std::vector<int> ids) {
    Circle2D defence_line(field.ourGoalCenter, 1);
    Segment2D ball_to_goal(field.ourGoalCenter, worldModel.ball.pos);
    auto bg_vector = field.ourGoalCenter - worldModel.ball.pos;
    auto amood = bg_vector.rotate(90).normalize();
    auto bg_vector2 = field.ourGoalCenter - worldModel.ball.pos;

    double dir = bg_vector2.rotate(90).th().degree();
    Vector2D sol1, sol2;
    if (defence_line.intersection(ball_to_goal, &sol1, &sol2)) {
        for (int i = 0; i < ids.size(); ++i) {
            double offset = 0;
            if (i == 1)
                offset = .35;
            if (i == 2)
                offset = -.35;

            gotopoint(ids[i], sol1 + (amood * offset),dir);
        }
    }
//    else
//        for (int i = 0; i < ids.size(); ++i) {
//
//            double theta = 180.0 / (ids.size() + 1) * (i + 1);
//            double x = sin(theta);
//            double y = cos(theta);
//            gotopoint(ids[i], field.ourGoalCenter + Vector2D(x, y));
//        }
}

#endif //PARSIAN_DEFENCE_H
