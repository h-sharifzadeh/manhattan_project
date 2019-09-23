//
// Created by parsian-ai on 9/14/19.
//

#ifndef PARSIAN_COACH_H
#define PARSIAN_COACH_H


void Soccer::execute() {

    Goalie(0);
    std::vector<int> robots{1, 2, 3, 4};
    double attatck_line = (attack_state == 1) ? -.6 : 0.6;

    double min_cost = 100000;
    double min_index = 4;
    for (int i = 1; i < 5; i++) {
        double cost = worldModel.ball.pos.dist(worldModel.ourRobots[i].pos);
        if (worldModel.ourRobots[i].pos.x > worldModel.ball.pos.x)
            cost *= 1;

        if (cost < min_cost) {
            min_cost = cost;
            min_index = i;
        }
    }
    robots.erase(robots.begin() + min_index -1);
    Playmake(min_index);


    if (worldModel.ball.pos.x > attatck_line) {
        attack_state = 1;
        Defence({robots[0]});
        Support({robots[1], robots[2]});

    } else {
        attack_state = 0;
        Defence({robots[0], robots[1], robots[2]});

    }

}

#endif //PARSIAN_COACH_H
