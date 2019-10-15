#include <soccer.h>

void Soccer::attacker(int id){
    Vector2D target{field.theirGoalCenter + Vector2D{0.3, 0}};
    Vector2D ballPos{wm->ball.pos + wm->ball.vel*0.2};
    double ballVel{wm->ball.vel.length()};
    Rect2D fieldWithMargin{field.cornerA + Vector2D{0, 0.4}, field.cornerC - Vector2D{0, 0.4}};
    if(!fieldWithMargin.contains(ballPos))
    {
        if(ballPos.dist(field.cornerB) > ballPos.dist(field.cornerC))
            target = field.cornerC;
        else
            target = field.cornerB;
    }
    else if(ballPos.x < 0)
    {
        target = ballPos + (ballPos - field.ourGoalCenter).normalizedVector()*1000;
    }
    std::cout << target << std::endl;


    kick(id,target);
}