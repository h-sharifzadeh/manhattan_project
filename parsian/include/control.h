#ifndef PARSIAN_CONTROL_H
#define PARSIAN_CONTROL_H


void Soccer::set_robot_vel(std::size_t id, double vel_f, double vel_w) {
    set_robot_wheel(id, vel_f + vel_w, vel_f - vel_w);
}


void Soccer::set_robot_wheel(std::size_t id, double leftWheel, double rightWheel) {
    if (id < 0 || id > info.number_of_robots - 1) {
        std::cerr << "trying to set an out of index robot wheel" << std::endl;
    }
    wheels[2 * id] = leftWheel;
    wheels[2 * id + 1] = rightWheel;
}


double Soccer::look_at(std::size_t id, rcsc::Vector2D pos) {

}

void Soccer::gotopoint(std::size_t id, rcsc::Vector2D pos) {
    auto ang = rcsc::AngleDeg::normalize_angle(
            worldModel.ourRobots.at(id).theta - (worldModel.ourRobots.at(id).pos - pos).dir().degree());
    auto last_ang = rcsc::AngleDeg::normalize_angle(
            lastWorldModel.ourRobots.at(id).theta - (lastWorldModel.ourRobots.at(id).pos - pos).dir().degree()) - ang;

    auto ang_thr = 35;
    auto go_toward = (ang > -ang_thr && ang < ang_thr) ? 1 : (ang > 180 - ang_thr && ang < -180 + ang_thr) ? -1 : 0;
    auto dist = pos.dist(worldModel.ourRobots.at(id).pos);
    auto last_dist = pos.dist(worldModel.ourRobots.at(id).pos) - dist;
    set_robot_vel(id, (-30 * dist - 2 * last_dist) * go_toward, ang * .01 + last_ang * .001);
}

#endif //PARSIAN_CONTROL_H
