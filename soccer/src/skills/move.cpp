#include <soccer.h>

void Soccer::move(int id, rcsc::Vector2D pos, double theta, double max_vel) {

    auto dir = rcsc::AngleDeg::normalize_angle((wm->ourRobots[id].pos - pos).dir().degree());
    auto error = wm->ourRobots[id].pos.dist(pos);
    if (error < 0.1) {
        dir = theta;
    }

    auto theta_error = rcsc::AngleDeg::normalize_angle(dir - wm->ourRobots[id].theta);

    double w = PID_ang[id].execute(theta_error);
    double normal_vel = PID_pos[id].execute(error);

    if (std::abs(theta_error) > 30 || error < 0.1) {
        setWheelsPID(id, 0, w, max_vel);
    } else {
        setWheelsPID(id, normal_vel, w, max_vel);
    }


}