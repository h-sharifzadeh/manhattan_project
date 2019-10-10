#include <soccer.h>

void Soccer::GK(int id)
{
    rcsc::Vector2D ballPos{worldModel.ball.pos + worldModel.ball.vel.normalizedVector()};
    rcsc::Line2D ballPath{ worldModel.ball.pos, worldModel.ball.pos + worldModel.ball.vel.normalizedVector()*1000 };
    rcsc::Line2D goalLine{ field.ourGoalU, field.ourGoalD };
    rcsc::Vector2D p;
    p = ballPath.intersection(goalLine);
    if (worldModel.ball.vel.length() < 0.5) p.invalidate();
    else if (ballPos.x < 2.9 && ballPos.y > info.goal[0]/2) p.invalidate();
    else if (ballPos.x < 2.9 && ballPos.y < -info.goal[0] / 2) p.invalidate();
    else if (ballPos.x > 1.5) p.invalidate();
    double y;
    bool forward{false};
    if (field.ourBigPenalty.contains(ballPos) && worldModel.ball.vel.length() < 1.5)
        forward = true;
    //p.invalidate();
    if (p.isValid()) {
        y = p.y;
    }
    else {
        y = worldModel.ball.pos.y + worldModel.ball.vel.y*1;
    }


    if (y < -info.goal[1] / 2 + 0.05) y = -info.goal[1] / 2 + 0.02;
    if (y > info.goal[1] / 2 - 0.05) y = info.goal[1] / 2 - 0.02;

    rcsc::Vector2D targetVel = rcsc::Vector2D(0, 1000);
    rcsc::Vector2D targetPos = rcsc::Vector2D(-info.field[0] / 2 + 0.02, y);
    if (worldModel.ourRobots[id].pos.x > -info.field[0] / 2 + 5) targetPos = field.ourGoalCenter;

    if (!forward) {
	    move(id, targetPos, 1, 90);
    } else {
	    fast(id, field.theirGoalCenter);
    }

    // SPIN
//    if (worldModel.ball.pos.dist(wm->ourRobot(id).pos) < 8.5 && worldModel.ball.vel.length() < 2) {
//        spin(id, worldModel.ball.pos, 30);
//    }
}