#include <soccer.h>

void Soccer::move(int id, rcsc::Vector2D pos, double max_vel, double theta) {
	auto dir = rcsc::AngleDeg::normalize_angle((worldModel.ourRobots[id].pos - pos).dir().degree());
	auto error = worldModel.ourRobots[id].pos.dist(pos);
	auto thr = error * 10 + 10;
	thr = fmin(thr, 60);
	
	auto abs_error = fabs(rcsc::AngleDeg::normalize_angle(dir - worldModel.ourRobots[id].theta));
	double normal_vel = PID_pos[id].execute(error);
	normal_vel = ((abs_error < thr || (180 - abs_error) < thr) ? normal_vel : 0);
	std::cout << normal_vel << std::endl;
	
	
	if (error < .03) {
		dir = theta;
		normal_vel = 0;
	}
	auto coef = 1.0;
	
	if (abs_error < 30)
		coef = 6.0 * (30 - abs_error) / 30.0;
	
	setVel(id, normal_vel * coef, dir, max_vel);
}
