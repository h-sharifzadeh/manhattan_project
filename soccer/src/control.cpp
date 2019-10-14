#include <soccer.h>

void Soccer::setWheels(int id, double leftWheel, double rightWheel, double max_wheel_speed) {
	if (id < 0 || id > info.number_of_robots - 1) {
		std::cerr << "trying to set an out of index robot wheel" << std::endl;
	}

	const double& rabs = std::abs(rightWheel);
	const double& labs = std::abs(leftWheel);

	if (rabs >= labs && rabs > max_wheel_speed) {
		double k = max_wheel_speed / rabs;
		rightWheel = max_wheel_speed * (rightWheel > 0 ? 1 : -1);
		leftWheel *= k;
	}
	else if (rabs < labs && labs > max_wheel_speed) {
		double k = max_wheel_speed / labs;
		leftWheel = max_wheel_speed * (leftWheel > 0 ? 1 : -1);
		rightWheel *= k;
	}
    //std::cout << leftWheel << ", " << rightWheel << std::endl;
    wheels[2 * id] = leftWheel;
	wheels[2 * id + 1] = rightWheel;
}

void Soccer::setWheelsPID(int id, double vel_tan, double _w, double max_speed) {

	double right_wheel = vel_tan + _w;
	double left_wheel = vel_tan - _w;

	setWheels(id, left_wheel, right_wheel, max_speed);
}

void Soccer::circleMove(int id, Vector2D center, double raduis, double w, double max_speed) {
    double v = raduis * w;
//    Circle2D c{center, raduis};
//    Vector2D a,b; a.invalidate(); b.invalidate();
//    auto num =  c.tangent(wm->ourRobots[id].pos, &a, &b);
//    Vector2D r; r = (a.isValid() ? a : (b.isValid() ? b : r));

    if (s == 0 && wm->ourRobots[id].pos.dist(wm->ball.pos - Vector2D(0.5, 0)) < 0.2 && std::abs(wm->ourRobots[id].theta - 90) < 10)s = 1;
    else if (s == 1 && wm->ourRobots[id].pos.dist(wm->ball.pos) > 1) s = 0;

    if (s == 0) {
        move(id, wm->ball.pos - Vector2D(0.5,0), 90);
    } else if (s == 1) {
        setWheelsPID(id, v, w, max_speed);
    }

//    if (wm->ourRobots[id].pos.dist(center) > raduis + 1) {
//        move(id, r, (r - wm->ourRobots[id].pos).th().degree(), max_speed);
//    } else {
//    }
}