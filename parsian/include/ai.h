#include "soccer.h"
#include "myprotobuf.h"
#include "control.h"
#include "knowledge.h"
//#include "geom/rect_2d.h"

void Soccer::decide() {

        if (worldModel.ourRobots.at(1).pos.x > info.field[0] / 3)
            last_point = {-info.field[0] / 2, 0};
        else if (worldModel.ourRobots.at(1).pos.x < -info.field[0] / 3)
            last_point = {info.field[0] / 2, 0};

        gotopoint(1, last_point);


}