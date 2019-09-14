//
// Created by parsian-ai on 9/14/19.
//

#ifndef PARSIAN_COACH_H
#define PARSIAN_COACH_H



void Soccer::execute() {

    Goalie(0);
    Playmake(4);

    double attatck_line = (attack_state == 1) ? -.6 : 0.6;

    if (worldModel.ball.pos.x > attatck_line){
        attack_state = 1;
//        Defence({1});
        Support({2,3});

    } else{
        attack_state = 0;
//        Defence({1,2,3});

    }




}

#endif //PARSIAN_COACH_H
