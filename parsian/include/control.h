#ifndef PARSIAN_CONTROL_H
#define PARSIAN_CONTROL_H

#include "soccer.h"






void Soccer::set_robot_wheel(std::size_t id, double leftWheel, double rightWheel)
{
    if(id < 0 || id > info.number_of_robots - 1)
    {
        std::cerr << "trying to set an out of index robot wheel" << std::endl;
    }
    wheels[2*id] = leftWheel;
    wheels[2*id + 1] = rightWheel;
}

void Soccer::set_robot_vel(std::size_t id, double vel_f, double angle)
{
    angle -= 180;
    PID_velN[id].run(vel_f - worldModel.ourRobots[id].vel.length());
    vel_f += PID_velN[id].lastOut;

    double error{rcsc::AngleDeg::normalize_angle(angle - worldModel.ourRobots[id].theta)};
    double vel_w = PID_ang[id].run(error);
    vel_w  = fabs(error) < 4 ? 0 : vel_w;
    //std::cout << vel_w << ", " << worldModel.ourRobots[id].theta << ", " << rcsc::AngleDeg::normalize_angle(angle - worldModel.ourRobots[id].theta) << std::endl;

    set_robot_wheel(id, vel_f + vel_w, vel_f - vel_w);
}




#endif //PARSIAN_CONTROL_H
