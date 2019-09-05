#ifndef PARSIAN_CONTROL_H
#define PARSIAN_CONTROL_H

#include "soccer.h"
#include "geom/circle_2d.h"
#include "geom/ray_2d.h"


void Soccer::set_robot_wheel(std::size_t id, double leftWheel, double rightWheel) {
    if (id < 0 || id > info.number_of_robots - 1) {
        std::cerr << "trying to set an out of index robot wheel" << std::endl;
    }
    wheels[2 * id] = leftWheel;
    wheels[2 * id + 1] = rightWheel;
}

void Soccer::set_robot_vel(std::size_t id, double vel_f, double angle, double max_vel) {
    double error{rcsc::AngleDeg::normalize_angle(angle - worldModel.ourRobots[id].theta)};


    vel_f = fmin(vel_f, max_vel);

    if (abs(error) > 90) {
        error = rcsc::AngleDeg::normalize_angle(angle + 180 - worldModel.ourRobots[id].theta);
        vel_f *= -1;
    }
    double vel_w = -PID_ang[id].run(error);

    // enhancement
    vel_f *= (90 - fabs(error)) / 50;

    vel_w = fmin(vel_w, .1);
    vel_w = fmax(vel_w, -.1);
//    std::cout<<"vel_f"<<vel_f<<std::endl;
//    std::cout<<"vel_w"<<vel_w<<std::endl;
    set_robot_wheel(id, -vel_f + vel_w, -vel_f - vel_w);
}


void Soccer::gotopoint(std::size_t id, rcsc::Vector2D pos, double max_vel, double theta) {
    auto dir = rcsc::AngleDeg::normalize_angle((worldModel.ourRobots[id].pos - pos).dir().degree());
    auto error = worldModel.ourRobots[id].pos.dist(pos);
    auto thr = error * 9 + 9;
    thr = fmin(thr, 85);

    thr = fmin(thr, 15);
    thr = fmax(thr, 3);

    auto abs_error = fabs(rcsc::AngleDeg::normalize_angle(dir - worldModel.ourRobots[id].theta));
    double normal_vel = PID_pos[id].run(error);
    normal_vel = ((abs_error < thr || (180 - abs_error) < thr) ? normal_vel : 0);


    if (error < .03) {
        dir = theta;
        normal_vel = 0;
    }

    set_robot_vel(id, normal_vel, dir, max_vel);
}


void Soccer::onetouch(std::size_t id, rcsc::Vector2D pos, double theta) {
    auto dir = rcsc::AngleDeg::normalize_angle((worldModel.ourRobots[id].pos - pos).dir().degree());
    auto error = worldModel.ourRobots[id].pos.dist(pos);
    auto thr = error * 12;
    double max_vel = 1;
    thr = fmin(thr, 15);
    thr = fmax(thr, 3);

    auto abs_error = fabs(rcsc::AngleDeg::normalize_angle(dir - worldModel.ourRobots[id].theta));
    double normal_vel = PID_pos[id].run(error);
    normal_vel = ((abs_error < thr || (180 - abs_error) < thr) ? normal_vel : 0);

    if (error < .5 || (abs_error < 3 || (180 - abs_error) < 3)) {
        normal_vel = 10.0;
        max_vel = 20.0;
    }

    set_robot_vel(id, normal_vel, dir, max_vel);
}

void Soccer::kick(int id, const rcsc::Vector2D &targetPos) {

    Vector2D ballPos{worldModel.ball.pos};
    Vector2D behindBallPos{ballPos + (ballPos - targetPos).normalizedVector()*0.2};
    double behindBallDeg{((ballPos - targetPos)*-1).dir().degree()};
    validatePos(behindBallPos);

    Vector2D avoidPos{(ballPos - targetPos).normalizedVector()*0.2};
    if(ballPos.y > 0)
        avoidPos = ballPos + avoidPos.rotate(90);
    else
        avoidPos = ballPos + avoidPos.rotate(-90);

    validatePos(avoidPos);



    gotopoint(id, avoidPos, 1, 0);
}



void Soccer::validatePos(rcsc::Vector2D &targetPos) {
    if(targetPos.x > info.field[0]/2)   targetPos.x = info.field[0]/2 - 0.08;
    if(targetPos.x < -info.field[0]/2)   targetPos.x = -info.field[0]/2 + 0.08;
    if(targetPos.y > info.field[1]/2)   targetPos.y = info.field[1]/2 - 0.08;
    if(targetPos.y < -info.field[1]/2)   targetPos.y = -info.field[1]/2 + 0.08;
}


#endif //PARSIAN_CONTROL_H
