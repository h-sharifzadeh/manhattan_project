#include <soccer.h>

void Soccer::kick(int id, const rcsc::Vector2D &targetPos) {
	
	double ROBOT_WIDTH{info.robot_size[id]};
	double ROBOT_HALF_WIDTH{ROBOT_WIDTH * 1};
	if (state != STATE::AVOID)
		ROBOT_HALF_WIDTH = {ROBOT_WIDTH * .5};
	double Field_width{info.field[0]};
	double Field_height{info.field[1]};
	
	
	rcsc::Vector2D ballPos{wm->ball.pos + wm->ball.vel * (.04)};
	rcsc::Vector2D robotPos{wm->ourRobots[id].pos + wm->ourRobots[id].vel * (.005)};
	rcsc::Vector2D norm{ballPos - targetPos};
	norm = norm.normalize();
	rcsc::Vector2D prependicular{norm.rotatedVector(90)};
	rcsc::Vector2D behindPos{ballPos + norm * .5 + wm->ball.vel * .12};
	rcsc::Vector2D avoidPos{ballPos + prependicular * .4};
	rcsc::Circle2D robotArea{robotPos, ROBOT_HALF_WIDTH * sqrt(2)};
	rcsc::Vector2D sol1, sol2;
//    if (behindPosIsValid(targetPos)) {
//        behindPos = lastBehinePos;
//    } else {
//        lastBehinePos = behindPos;
//    }
	if (robotArea.intersection(rcsc::Segment2D{ballPos, targetPos}, &sol1, &sol2) > 0) {
		if (state == STATE::KICK) {
			if (robotPos.x > wm->ball.pos.x)
				state = STATE::AVOID;
		} else
			state = STATE::AVOID;
		
	} else if (state != STATE::KICK) {
		if (wm->ourRobots[id].pos.dist(behindPos) < .1)
			state = STATE::KICK;
		else
			state = STATE::BEHIND;
	} else if (robotPos.x > wm->ball.pos.x + .1)
		state = state = STATE::BEHIND;


//    if (avoidPos.x < -Field_width / 2 + ROBOT_WIDTH || avoidPos.x > Field_width / 2 + ROBOT_WIDTH ||
//        avoidPos.y < -Field_height / 2 + ROBOT_WIDTH || avoidPos.x > Field_height / 2 + ROBOT_WIDTH)
//        state = STATE::KICK;
	
	switch (state) {
		
		case AVOID:
			move(id, avoidPos);
			std::cout << "avoid" << std::endl;
			
			break;
		case BEHIND:
			move(id, behindPos);
			std::cout << "behind" << std::endl;
			
			break;
		case KICK:
			if (ballPos.dist(robotPos) < .25) {
				//fast kick
				
				move(id, ballPos - norm * 2, 3);
				
			} else
				move(id, ballPos, 5);
			std::cout << "kikckkkkkk" << std::endl;
			
			break;
	}
	
}