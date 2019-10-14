#include <soccer.h>

#include <math.h>
#include "ploterProtobuf.h"

Soccer::Soccer(const std::string& server_ip, std::size_t port, const std::string& realm, std::string key, std::string datapath)
        : ai_base(server_ip, port, realm, key, std::move(datapath)) {

    wm = new WorldModel();
    lwm = new WorldModel();

    for (auto& wheel : wheels) wheel = 0;

    PID_ang[GK_ID].kp = -0.6 * M_PI / 180.0;
    PID_ang[GK_ID].kd = 0.0125;
    PID_ang[GK_ID].ki = 0.0;

    PID_ang[DEF1_ID].kp = PID_ang[DEF2_ID].kp = -0.6 * M_PI / 180.0;
    PID_ang[DEF1_ID].kd = PID_ang[DEF2_ID].kd = 0.0125;
    PID_ang[DEF1_ID].ki = PID_ang[DEF2_ID].ki = 0.0;

    PID_ang[ATT1_ID].kp = PID_ang[ATT2_ID].kp = -0.2 * M_PI / 180.0;
    PID_ang[ATT1_ID].kd = PID_ang[ATT2_ID].kd = 0.0;
    PID_ang[ATT1_ID].ki = PID_ang[ATT2_ID].ki = 0.0;

    PID_pos[GK_ID].kp = -6;
    PID_pos[GK_ID].kd = 0.0;
    PID_pos[GK_ID].ki = 0.0;

    PID_pos[DEF1_ID].kp = PID_pos[DEF2_ID].kp = -6;
    PID_pos[DEF1_ID].kd = PID_pos[DEF2_ID].kd = 0.0;
    PID_pos[DEF1_ID].ki = PID_pos[DEF2_ID].ki = 0.0;

    PID_pos[ATT1_ID].kp = PID_pos[ATT2_ID].kp = -2;
    PID_pos[ATT1_ID].kd = PID_pos[ATT2_ID].kd = 0.0;
    PID_pos[ATT1_ID].ki = PID_pos[ATT2_ID].ki = 0.0;

    initServer();
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
    *lwm = *wm;
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
        double tempW = wm->ourRobots[i].theta - lwm->ourRobots[i].theta;
        if (tempW > 100) {
            wm->ourRobots[i].angularVel = lwm->ourRobots[i].angularVel;
            //wm->ourRobots[i].angularVel = rcsc::AngleDeg::normalize_angle(tempW - 360);
        } else if (tempW < -100) {
            wm->ourRobots[i].angularVel = lwm->ourRobots[i].angularVel;
            //wm->ourRobots[i].angularVel = rcsc::AngleDeg::normalize_angle(360 - tempW);
        } else {
            wm->ourRobots[i].angularVel = rcsc::AngleDeg::normalize_angle(tempW);
        }
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
                rcsc::AngleDeg::normalize_angle(-wm->oppRobots[i].theta - lwm->oppRobots[i].theta);// deg/s(50 ms each frame)
    }
    //ball
    wm->ball.pos.x = f.opt_coordinates->ball.x;
    wm->ball.pos.y = -f.opt_coordinates->ball.y;
    wm->ball.vel = (wm->ball.pos - lwm->ball.pos) * 20;// m/s(50 ms each frame)
}

void Soccer::updateField() {
	field.update(info);
}


