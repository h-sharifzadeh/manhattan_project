#include <soccer.h>

#include <math.h>
#include "ploterProtobuf.h"

Soccer::Soccer(const std::string& server_ip, std::size_t port, const std::string& realm, std::string key, std::string datapath)
        : ai_base(server_ip, port, realm, key, std::move(datapath)) {

    wm = new WorldModel();
    lwm = new WorldModel();

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
    lwm = wm;
    sendWorldModelMessage(wm);
}

void Soccer::updateWorldModel(const aiwc::frame &f) {
    //our robots
    for (size_t i{}; i < info.number_of_robots; i++) {
        wm->ourRobots[i].id = i;
        wm->ourRobots[i].pos.x = f.opt_coordinates->robots[0][i].x;
        wm->ourRobots[i].pos.y = -f.opt_coordinates->robots[0][i].y;
        wm->ourRobots[i].vel =
                (wm->ourRobots[i].pos - lwm->ourRobots[i].pos) * 20;// m/s(50 ms each frame)
        wm->ourRobots[i].active = f.opt_coordinates->robots[0][i].active;
        wm->ourRobots[i].theta = rcsc::AngleDeg::normalize_angle(-
                f.opt_coordinates->robots[0][i].th * rcsc::AngleDeg::RAD2DEG);
        wm->ourRobots[i].angularVel =
                rcsc::AngleDeg::normalize_angle(wm->ourRobots[i].theta - lwm->ourRobots[i].theta) * 20;// deg/s(50 ms each frame)
    }
    //opp robots
    for (size_t i{}; i < info.number_of_robots; i++) {
        wm->oppRobots[i].id = i;
        wm->oppRobots[i].pos.x = f.opt_coordinates->robots[1][i].x;
        wm->oppRobots[i].pos.y = -f.opt_coordinates->robots[1][i].y;
        wm->oppRobots[i].vel =
                (wm->oppRobots[i].pos - lwm->oppRobots[i].pos) * 20;// m/s(50 ms each frame)
        wm->oppRobots[i].active = f.opt_coordinates->robots[1][i].active;
        wm->oppRobots[i].theta = rcsc::AngleDeg::normalize_angle(
                f.opt_coordinates->robots[1][i].th * rcsc::AngleDeg::RAD2DEG);
        wm->oppRobots[i].angularVel =
                rcsc::AngleDeg::normalize_angle(-wm->oppRobots[i].theta - lwm->oppRobots[i].theta) * 20;// deg/s(50 ms each frame)
    }
    //ball
    wm->ball.pos.x = f.opt_coordinates->ball.x;
    wm->ball.pos.y = -f.opt_coordinates->ball.y;
    wm->ball.vel = (wm->ball.pos - lwm->ball.pos) * 20;// m/s(50 ms each frame)
}

void Soccer::updateField() {
	field.update(info);
}


