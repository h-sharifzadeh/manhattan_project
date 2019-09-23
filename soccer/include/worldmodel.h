#ifndef DELFT_SOCCER_WORLDMODEL_H
#define DELFT_SOCCER_WORLDMODEL_H

#include <vector_2d.h>
#include <rect_2d.h>
#include <array>

using namespace rcsc;

enum EROBOT_ID {
	GK_ID   = 0,
	DEF1_ID = 1,
	DEF2_ID = 2,
	ATT1_ID = 3,
	ATT2_ID = 4
};

struct MovingObject {
	Vector2D pos{0, 0};
	Vector2D vel{0, 0};
	Vector2D acc{0, 0};
};

struct Robot : public MovingObject {

	std::size_t id{};
	bool active{true};
	double theta{};
	double angularVel{};
};

struct WorldModel
{
	std::array<Robot, 5> ourRobots;
	std::array<Robot, 5> oppRobots;
	MovingObject ball{};
};
#endif //DELFT_SOCCER_WORLDMODEL_H
