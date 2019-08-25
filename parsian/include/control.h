#ifndef PARSIAN_CONTROL_H
#define PARSIAN_CONTROL_H

void Soccer::set_robot_wheel(std::size_t id, double leftWheel, double rightWheel)
{
    if(id < 0 || id > info.number_of_robots - 1)
    {
        std::cerr << "trying to set an out of index robot wheel" << std::endl;
    }
    wheels[2*id] = leftWheel;
    wheels[2*id + 1] = rightWheel;
}


#endif //PARSIAN_CONTROL_H
