#include <soccer.h>

void Soccer::setWheels(int id, double leftWheel, double rightWheel) {
	if (id < 0 || id > info.number_of_robots - 1) {
		std::cerr << "trying to set an out of index robot wheel" << std::endl;
	}
	const double max_wheel_speed = 2.5;

	if (rightWheel >= leftWheel && rightWheel > max_wheel_speed) {
		double k = max_wheel_speed / rightWheel;
		rightWheel = max_wheel_speed;
		leftWheel *= k;
	}
	else if (rightWheel < leftWheel && leftWheel > max_wheel_speed) {
		double k = max_wheel_speed / leftWheel;
		leftWheel = max_wheel_speed;
		rightWheel *= k;
	}
	wheels[2 * id] = leftWheel;
	wheels[2 * id + 1] = rightWheel;
}

PID w[5];
void Soccer::setWheelsPID(int id, double vel_tan, double _w) {

	w[id].kp = 1; w[id].ki = 0; w[id].kd = 0.2;
	_w += _w;
	w[id].execute(_w - wm->ourRobots[id].angularVel);
	double w_o = (_w != 0 ) ? w[id].lastOut : 0;

	//wheel =  a*x
	double a{ 1 };
	double right_vel_tan{ a * vel_tan };
	double left_vel_tan{ a * vel_tan };
	//solve w
	//wheel = a*w
	double a1{ 1 };
	double right_vel_w{ a1 * w_o };
	double left_vel_w{ -a1 * w_o };
	double right_wheel = right_vel_tan + right_vel_w;
	double left_wheel = left_vel_tan + left_vel_w;

	setWheels(id, left_wheel, right_wheel);
}

void Soccer::setVel(int id, double vel_f, double w, double max_vel) {
//	setWheels(id, -vel_f + vel_w, -vel_f - vel_w);
}