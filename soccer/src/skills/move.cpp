#include <soccer.h>

void Soccer::move(int id, rcsc::Vector2D pos, double max_vel, double theta) {

	auto dir = rcsc::AngleDeg::normalize_angle((wm->ourRobots[id].pos - pos).dir().degree());
	auto error = wm->ourRobots[id].pos.dist(pos);

	std::cout << "salam" << dir << std::endl;
	auto abs_error = fabs(rcsc::AngleDeg::normalize_angle(dir - wm->ourRobots[id].theta));
	double normal_vel = PID_pos[id].execute(error);
    std::cout << "salam" << abs_error << std::endl;

    if (error < .03) {
		dir = theta;
		normal_vel = 0;
	} else  {
        if (abs_error > 30) {
            dir = theta;
            normal_vel = 0;
        } else {
            dir = wm->ourRobots[id].theta;
        }
	}

    setVel(id, normal_vel, dir, max_vel);
}