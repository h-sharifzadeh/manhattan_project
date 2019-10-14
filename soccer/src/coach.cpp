#include <soccer.h>

#include <fstream>

std::ifstream file;

void Soccer::coach() {
    double a[10];
    file.open("a.txt");
    for(auto& f : a) {
        file >> f;
    }
    file.close();
    setWheelsPID((int)(a[0]),a[1],a[2]);

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