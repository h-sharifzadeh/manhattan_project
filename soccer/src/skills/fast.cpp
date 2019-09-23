#include <soccer.h>

void Soccer::fast(int id, rcsc::Vector2D pos, double theta) {
    auto dir = rcsc::AngleDeg::normalize_angle((worldModel.ourRobots[id].pos - pos).dir().degree());
    auto error = worldModel.ourRobots[id].pos.dist(pos);
    auto thr = error * 12;
    double max_vel = 1;
    thr = fmin(thr, 15);
    thr = fmax(thr, 3);

    auto abs_error = fabs(rcsc::AngleDeg::normalize_angle(dir - worldModel.ourRobots[id].theta));
    double normal_vel = PID_pos[id].execute(error);
    normal_vel = ((abs_error < thr || (180 - abs_error) < thr) ? normal_vel : 0);

    if (error < .5 || (abs_error < 3 || (180 - abs_error) < 3)) {
        normal_vel = 10.0;
        max_vel = 20.0;
    }
	
	setVel(id, normal_vel, dir, max_vel);
}
