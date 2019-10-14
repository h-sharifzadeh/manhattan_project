#include <soccer.h>

enum class KickState{
    avoid,
    behind,
    shot,
    none
};
KickState kickState = KickState::behind;

void Soccer::kick(int id, const rcsc::Vector2D &targetPos) {
    Vector2D ballPos{wm->ball.pos};
    Vector2D robotPos{wm->ourRobots[id].pos + wm->ourRobots[id].vel*0.2};
    if(robotPos.dist(ballPos) < robotPos.dist(ballPos + wm->ball.vel*0.5))
        ballPos += wm->ball.vel*0.4;
    else
        ballPos -= wm->ball.vel*0.4;
    Circle2D smallArea{ballPos, 0.2};
    Circle2D bigArea{ballPos, 0.4};
    Vector2D behindPos{ballPos + (ballPos - targetPos).normalizedVector()*0.35};
    Vector2D frontPos{ballPos + (targetPos - ballPos).normalizedVector()*0.35};
    Vector2D temp{(ballPos - targetPos)};
    Vector2D avoidPos{ballPos + temp.rotate(90).normalizedVector()*0.35};
    Segment2D robotPath{wm->ourRobots[id].pos, behindPos};



    Vector2D sol1, sol2, sol3, sol4;
    sol1.invalidate(); sol2.invalidate(); sol3.invalidate(); sol4.invalidate();

    bool intersectBig = bigArea.intersection(robotPath, &sol3, &sol4);
    bool intersectSmall = smallArea.intersection(robotPath, &sol1, &sol2);

    double threshold{(kickState == KickState::shot ? 0.55 : 0.18)};
    if (robotPos.dist(behindPos) < threshold)
        kickState = KickState::shot;
    else if(!intersectBig && !intersectSmall){
        kickState = KickState::behind;
    } else if(intersectBig && !intersectSmall){
        kickState = (robotPos.dist(behindPos) < robotPos.dist(frontPos) ? KickState::behind : KickState::avoid);
    }else {
        kickState = KickState::avoid;
    }


    switch(kickState)
    {
        case KickState::avoid:
            std::cout << "avoid " << std::endl;
            move(id, avoidPos, behindPos.dir().degree());
            break;
        case KickState::behind:
            std::cout << "behind " << std::endl;
            move(id, behindPos, targetPos.dir().degree());
            break;
        case KickState::shot:
            std::cout << "shot " << std::endl;
            move(id, ballPos + wm->ball.vel, ballPos.dir().degree());
            break;
        default:
            std::cout << "none " << std::endl;

            break;
    }
}