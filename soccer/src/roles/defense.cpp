#include <soccer.h>

void Soccer::defense(std::vector<int> ids) {
	rcsc::Circle2D defence_line(field.ourGoalCenter, 1);
	Segment2D ball_to_goal(field.ourGoalCenter, wm->ball.pos);
	auto bg_vector = field.ourGoalCenter - wm->ball.pos;
	auto amood = bg_vector.rotate(90).normalize();
	auto bg_vector2 = field.ourGoalCenter - wm->ball.pos;
	
	double dir = bg_vector2.rotate(90).th().degree();
	Vector2D sol1, sol2;
	if (defence_line.intersection(ball_to_goal, &sol1, &sol2)) {
		for (int i = 0; i < ids.size(); ++i) {
			double offset = 0;
			if (i == 1)
				offset = .35;
			if (i == 2)
				offset = -.35;
			
			move(ids[i], sol1 + (amood * offset), dir);
		}
	}
}
