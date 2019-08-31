#ifndef PARSIAN_CONTROL_H
#define PARSIAN_CONTROL_H

#include "soccer.h"


void Soccer::set_robot_wheel(std::size_t id, double leftWheel, double rightWheel) {
    if (id < 0 || id > info.number_of_robots - 1) {
        std::cerr << "trying to set an out of index robot wheel" << std::endl;
    }
    wheels[2 * id] = leftWheel;
    wheels[2 * id + 1] = rightWheel;
}

void Soccer::set_robot_vel(std::size_t id, double vel_f, double angle,double max_vel) {
    double error{rcsc::AngleDeg::normalize_angle(angle - worldModel.ourRobots[id].theta)};


    std::cout<<"ffff   "<<vel_f<<std::endl;


    if (vel_f > 0) {
        vel_f = fmin(vel_f,max_vel);
    }

    if (abs(error) > 90) {
        error = rcsc::AngleDeg::normalize_angle(angle + 180 - worldModel.ourRobots[id].theta);
        vel_f *= -1;
    }
    double vel_w = -PID_ang[id].run(error);

//    std::cout<<"wwww   "<<vel_w<<std::endl;
//    std::cout<<"-------   "<<std::endl;

//    if (vel_w > 0)
//        vel_w = fmin(vel_w,.1);
//    else
//        vel_w = fmax(vel_w,-.1);


//    if(vel_f != 0)
//        vel_w /= 100.0;
    set_robot_wheel(id, -vel_f + vel_w, -vel_f - vel_w);
}


void Soccer::gotopoint(std::size_t id, rcsc::Vector2D pos,double theta) {
    auto dir = rcsc::AngleDeg::normalize_angle((worldModel.ourRobots[id].pos - pos).dir().degree());
    auto error = worldModel.ourRobots[id].pos.dist(pos);
//    auto thr = error * 5;
    auto thr = error * 12;
    double max_vel = .95;
    thr = fmin(thr, 15);
    thr = fmax(thr,3);

    auto abs_error = abs(rcsc::AngleDeg::normalize_angle(dir - worldModel.ourRobots[id].theta));
    double normal_vel = PID_pos[id].run(error);
    normal_vel = ((abs_error < thr || (180 - abs_error) < thr) ? normal_vel : 0);

    if (normal_vel < 0)
        std::cout<<normal_vel<<std::endl;

    if (error < .1) {
        dir = theta;
    }

    set_robot_vel(id, normal_vel, dir,max_vel);
}


void Soccer::kick(std::size_t id, rcsc::Vector2D pos,double theta) {
    auto dir = rcsc::AngleDeg::normalize_angle((worldModel.ourRobots[id].pos - pos).dir().degree());
    auto error = worldModel.ourRobots[id].pos.dist(pos);
//    auto thr = error * 5;
    auto thr = error * 12;
    double max_vel = .95;
    thr = fmin(thr, 15);
    thr = fmax(thr,3);

    auto abs_error = abs(rcsc::AngleDeg::normalize_angle(dir - worldModel.ourRobots[id].theta));
    double normal_vel = PID_pos[id].run(error);
    normal_vel = ((abs_error < thr || (180 - abs_error) < thr) ? normal_vel : 0);

    if (normal_vel < 0)
        std::cout<<normal_vel<<std::endl;

//    std::cout<<id<<"  "<<abs_error<<std::endl;

    if (error < .5 || (abs_error < 3 || (180 - abs_error) < 3) ) {
//        dir = theta;
        normal_vel = 10.0;
        max_vel = 20.0;
    }

    set_robot_vel(id, normal_vel, dir,max_vel);
}


#endif //PARSIAN_CONTROL_H
