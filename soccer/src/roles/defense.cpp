#include <soccer.h>


void Soccer::defense(std::vector<int> ids) {
    Ray2D ball_path(wm->ball.pos,wm->ball.pos + wm->ball.vel);

    Vector2D sol1,sol2;
    Ray2D our_goal(field.ourGoalD,field.ourGoalU);
    switch (ids.size()) {
    case 1:{
        int id = ids[0];

        if (ball_path.intersection(our_goal).dist(field.ourGoalCenter) < 1){
            Ray2D normal_path( wm->oppRobots[id].pos,wm->ourRobots[id].pos + wm->ball.vel.rotate(90));
            Vector2D waitpos = normal_path.intersection(ball_path);
            move(id,waitpos);
            break;
        }
        Ray2D ball_to_goal(field.ourGoalCenter,wm->ball.pos);
        int count = field.ourSmallPenalty.intersection(ball_to_goal,&sol1,&sol2);
        double dir = 0;
        Vector2D *sol;
        if ( count == 1)
             sol = &sol1;
        else if (count == 2){
            if (sol1.x < sol2.x)
                sol = &sol2;
            else
                sol = &sol1;
        }
        if (sol->x > field.ourSmallPenaltyC.x - .05)
            dir = 90;
        move(id,*sol,dir);

        }
        break;
    case 2:{




    }
        break;
    default:
        break;
    }

}


