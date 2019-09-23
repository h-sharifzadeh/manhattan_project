#include <soccer.h>

void Soccer::setWheels(int id, double leftWheel, double rightWheel) {
	if (id < 0 || id > info.number_of_robots - 1) {
		std::cerr << "trying to set an out of index robot wheel" << std::endl;
	}
	wheels[2 * id] = leftWheel;
	wheels[2 * id + 1] = rightWheel;
}

void Soccer::setVel(int id, double vel_f, double angle, double max_vel) {
	double error{rcsc::AngleDeg::normalize_angle(angle - worldModel.ourRobots[id].theta)};
	
	
	vel_f = fmin(vel_f, max_vel);
	
	if (fabs(error) > 90) {
		error = rcsc::AngleDeg::normalize_angle(angle + 180 - worldModel.ourRobots[id].theta);
		vel_f *= -1;
	}
	double vel_w = PID_ang[id].execute(error);
	
	// enhancement
	vel_f *= (90 - fabs(error)) / 50;
	
	vel_w = fmin(vel_w, .11);
	vel_w = fmax(vel_w, -.11);
//    std::cout<<"vel_w"<<vel_w<<std::endl;
	setWheels(id, -vel_f + vel_w, -vel_f - vel_w);
}