#include <soccer.h>

#include <fstream>

std::ifstream file;
double p_error = 0;
void Soccer::coach() {
    double a[10];
    file.open("a.txt");
    for(auto& f : a) {
        file >> f;
    }
    file.close();

    kick(3,field.theirGoalCenter);
//    circleMove((int)(a[0]), Vector2D(a[1], a[2]), a[3], a[4]);
//    setWheelsPID((int)(a[0]),a[1], a[2]);

    return;

    move((int)(a[0]),wm->ball.pos + wm->ball.vel, (wm->ball.pos - wm->ourRobots[a[0]].pos).th().degree(), a[1]);
    return;
    GK(0);

    std::vector<int> robots{1, 2, 3, 4};
    double attatck_line = (attack_state == 1) ? -.6 : 0.6;

    double min_cost = 100000;
    double min_index = 4;
    for (int i = 1; i < 5; i++) {
        double cost = wm->ball.pos.dist(wm->ourRobots[i].pos);
        if (wm->ourRobots[i].pos.x > wm->ball.pos.x)
            cost *= 1;

        if (cost < min_cost) {
            min_cost = cost;
            min_index = i;
        }
    }
    robots.erase(robots.begin() + min_index -1);
	attacker(min_index);


    if (wm->ball.pos.x > attatck_line) {
        attack_state = 1;
	    defense({robots[0]});
//        fast({robots[1], robots[2]});

    } else {
        attack_state = 0;
	    defense({robots[0], robots[1], robots[2]});

    }

}