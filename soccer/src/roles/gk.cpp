#include <soccer.h>


void Soccer::GK(int id)
{
    rcsc::Vector2D ballPos{wm->ball.pos + wm->ball.vel.normalizedVector()};
    rcsc::Line2D ballPath{ wm->ball.pos, wm->ball.pos + wm->ball.vel.normalizedVector()*1000 };
    rcsc::Line2D goalLine{ field.ourGoalU, field.ourGoalD };
    rcsc::Vector2D p;
    p = ballPath.intersection(goalLine);
    if (wm->ball.vel.length() < 0.5) p.invalidate();
    else if (ballPos.x < 2.9 && ballPos.y > info.goal[0]/2) p.invalidate();
    else if (ballPos.x < 2.9 && ballPos.y < -info.goal[0] / 2) p.invalidate();
    else if (ballPos.x > 1.5) p.invalidate();
    double y;
    bool forward{false};
	bool touchone{false};
    if (field.ourBigPenalty.contains(ballPos) && (wm->oppRobots[1].pos - ballPos).length() < 1.5 && (wm->oppRobots[2].pos - ballPos).length() < 1.5 && (wm->oppRobots[3].pos - ballPos).length() < 1.5 && (wm->oppRobots[4].pos - ballPos).length() < 1.5 )
        forward = true;
    //p.invalidate();
    if (p.isValid()) {
        y = p.y;
	   touchone = true;  
    }
    else {
        y = wm->ball.pos.y + wm->ball.vel.y*1;
    }

    if (y < -info.goal[1] / 2 + 0.05) y = -info.goal[1] / 2 + 0.03;
    if (y > info.goal[1] / 2 - 0.05) y = info.goal[1] / 2 - 0.03;

    rcsc::Vector2D targetVel = rcsc::Vector2D(0, 1000);
    rcsc::Vector2D targetPos = rcsc::Vector2D(-info.field[0] / 2 + 0.02, y);
    if (wm->ourRobots[id].pos.x > -info.field[0] / 2 + 5) targetPos = field.ourGoalCenter;

    if (!forward && !touchone) {
	    move(id, Vector2D{field.ourGoalU.x ,ballPos.y} , 1, 90);
    } else if (!forward && touchone) {
	    move(id, targetPos, 1, 90);
    } else {
	    fast(id, field.theirGoalCenter);
    }

    // SPIN
//    if (wm->ball.pos.dist(wm->ourRobot(id).pos) < 8.5 && wm->ball.vel.length() < 2) {
//        spin(id, wm->ball.pos, 30);
//    }




}
