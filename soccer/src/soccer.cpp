#include <soccer.h>

#include <math.h>
#include "ploterProtobuf.h"

Soccer::Soccer(const std::string& server_ip, std::size_t port, const std::string& realm, std::string key, std::string datapath)
        : ai_base(server_ip, port, realm, key, datapath) {
    for (auto& wheel : wheels) wheel = 0;
	
    for (auto& pid : PID_ang) {
	    pid.kp = 0.016;
	    pid.kd = 0.003;
	    pid.ki = 0.0;
    }
	for (auto& pid : PID_pos) {
		pid.kp = 2.9;
		pid.kd = 0.3;
		pid.ki = 0.0;
	}
//
//    PID_ang[GK_ID].kd = .35 / 100.0;
//
//    PID_pos[GK_ID].kp = 2.2;



}

void Soccer::init() {
    updateField();
}

void Soccer::finish() { /// TODO: Save config
}

void Soccer::update(const aiwc::frame &f) {
    updateWorldModel(f);
    
    coach();
    set_wheel(wheels);      //set all robots' wheels
    lastWorldModel = worldModel;
    sendWorldModelMessage(worldModel);
}

void Soccer::updateWorldModel(const aiwc::frame &f) {
    //our robots
    for (size_t i{}; i < info.number_of_robots; i++) {
        worldModel.ourRobots[i].id = i;
        worldModel.ourRobots[i].pos.x = f.opt_coordinates->robots[0][i].x;
        worldModel.ourRobots[i].pos.y = -f.opt_coordinates->robots[0][i].y;
        worldModel.ourRobots[i].vel =
                (worldModel.ourRobots[i].pos - lastWorldModel.ourRobots[i].pos) * 20;// m/s(50 ms each frame)
        worldModel.ourRobots[i].active = f.opt_coordinates->robots[0][i].active;
        worldModel.ourRobots[i].theta = rcsc::AngleDeg::normalize_angle(-
                f.opt_coordinates->robots[0][i].th * rcsc::AngleDeg::RAD2DEG);
        worldModel.ourRobots[i].angularVel =
                rcsc::AngleDeg::normalize_angle(worldModel.ourRobots[i].theta - lastWorldModel.ourRobots[i].theta) *
                20;// deg/s(50 ms each frame)
    }
    //opp robots
    for (size_t i{}; i < info.number_of_robots; i++) {
        worldModel.oppRobots[i].id = i;
        worldModel.oppRobots[i].pos.x = f.opt_coordinates->robots[1][i].x;
        worldModel.oppRobots[i].pos.y = -f.opt_coordinates->robots[1][i].y;
        worldModel.oppRobots[i].vel =
                (worldModel.oppRobots[i].pos - lastWorldModel.oppRobots[i].pos) * 20;// m/s(50 ms each frame)
        worldModel.oppRobots[i].active = f.opt_coordinates->robots[1][i].active;
        worldModel.oppRobots[i].theta = rcsc::AngleDeg::normalize_angle(
                f.opt_coordinates->robots[1][i].th * rcsc::AngleDeg::RAD2DEG);
        worldModel.oppRobots[i].angularVel =
                rcsc::AngleDeg::normalize_angle(-worldModel.oppRobots[i].theta - lastWorldModel.oppRobots[i].theta) *
                20;// deg/s(50 ms each frame)
    }
    //ball
    worldModel.ball.pos.x = f.opt_coordinates->ball.x;
    worldModel.ball.pos.y = -f.opt_coordinates->ball.y;
    worldModel.ball.vel = (worldModel.ball.pos - lastWorldModel.ball.pos) * 20;// m/s(50 ms each frame)
}

void Soccer::updateField() {
	field.update(info);
}


