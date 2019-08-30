#include "soccer.h"
#include "myprotobuf.h"
#include "control.h"

Soccer::Soccer(std::string server_ip, std::size_t port, std::string realm, std::string key, std::string datapath)
        : ai_base(std::move(server_ip), port, std::move(realm), std::move(key), std::move(datapath))
{
    std::cout << "PARSIAN TEAM start" << std::endl;
    gameState = GameState::playOn;
    for(int i{}; i <10; i++)
        wheels[i] = 0;
    initServer();
    //control
    #ifdef USE_DEBUG1
    std::ifstream pid;
    for(int i{}; i < 5; i++)
    {
        pid.open("pid.txt", std::_S_in);
        std::string title;
        pid >> title;
        pid >> PID_velN[i].kp >> PID_velN[i].ki >> PID_velN[i].kd;
        pid >> title;
        pid >> PID_ang[i].kp >> PID_ang[i].ki >> PID_ang[i].kd;
        pid >> title;
        pid >> PID_pos[i].kp >> PID_pos[i].ki >> PID_pos[i].kd;
        pid.close();
    }
    #else
    for(int i{}; i < 5; i++)
    {
        PID_velN[i].kp =  .6;
        PID_velN[i].kd =  .12;
        PID_velN[i].ki =  .02;

        PID_ang[i].kp =  20 / 10000.0;
        PID_ang[i].kd =  .2 / 10000.0;
        PID_ang[i].ki =  .1 / 10000.0;
    }
    #endif


}

void Soccer::init()
{
}

void Soccer::finish()
{
    std::cout << "PARSIAN TEAM finish" << std::endl;
}

void Soccer::update(const aiwc::frame &f)
{
    gameState = decideGameState(f.game_state, f.ball_ownership);
    updateWorldModel(f);

    set_robot_vel(2, 0, 60);
    set_wheel(wheels);      //set all robots' wheels
    lastWorldModel = worldModel;
    sendWorldModelMessage(worldModel);
}

GameState Soccer::decideGameState(std::size_t gamestate, bool ballownership)
{
    GameState _gameState;
    if(ballownership)
    {
        switch(gamestate)
        {
            case 0:
                _gameState = GameState::playOn;
                break;
            case 1:
                _gameState = GameState::ourKickOff;
                break;
            case 2:
                _gameState = GameState::ourGoalKick;
                break;
            case 3:
                _gameState = GameState::ourCornerKick;
                break;
            case 4:
                _gameState = GameState::ourPenaltyKick;
                break;
            default:
                _gameState = GameState::playOn;
                break;
        }
    }
    else
    {
        switch(gamestate)
        {
            case 0:
                _gameState = GameState::playOn;
                break;
            case 1:
                _gameState = GameState::theirKickOff;
                break;
            case 2:
                _gameState = GameState::theirGoalKick;
                break;
            case 3:
                _gameState = GameState::theirCornerKick;
                break;
            case 4:
                _gameState = GameState::theirPenaltyKick;
                break;
            default:
                _gameState = GameState::playOn;
                break;
        }
    }
    return _gameState;
}

std::string Soccer::gameStateToString(const GameState &gamestate) {
    switch(gamestate)
    {
        case GameState::playOn:
            return "playOn";
        case GameState::ourKickOff:
            return "ourKickOff";
        case GameState::theirKickOff:
            return "theirKickOff";
        case GameState::ourGoalKick:
            return "ourGoalKick";
        case GameState::theirGoalKick:
            return "theirGoalKick";
        case GameState::ourCornerKick:
            return "ourCornerKick";
        case GameState::theirCornerKick:
            return "theirCornerKick";
        case GameState::ourPenaltyKick:
            return "ourPenaltyKick";
        case GameState::theirPenaltyKick:
            return "theirPenaltyKick";
    }
}

void Soccer::updateWorldModel(const aiwc::frame &f) {
    //our robots
    for(size_t i{}; i < info.number_of_robots; i++)
    {
        worldModel.ourRobots[i].id = i;
        worldModel.ourRobots[i].pos.x = f.opt_coordinates->robots[0][i].x;
        worldModel.ourRobots[i].pos.y = f.opt_coordinates->robots[0][i].y;
        worldModel.ourRobots[i].vel = (worldModel.ourRobots[i].pos - lastWorldModel.ourRobots[i].pos) * 20;// m/s(50 ms each frame)
        worldModel.ourRobots[i].active = f.opt_coordinates->robots[0][i].active;
        worldModel.ourRobots[i].theta = rcsc::AngleDeg::normalize_angle(f.opt_coordinates->robots[0][i].th * rcsc::AngleDeg::RAD2DEG);
        worldModel.ourRobots[i].angularVel = rcsc::AngleDeg::normalize_angle(worldModel.ourRobots[i].theta - lastWorldModel.ourRobots[i].theta) * 20;// deg/s(50 ms each frame)
    }
    //opp robots
    for(size_t i{}; i < info.number_of_robots; i++)
    {
        worldModel.oppRobots[i].id = i;
        worldModel.oppRobots[i].pos.x = f.opt_coordinates->robots[1][i].x;
        worldModel.oppRobots[i].pos.y = f.opt_coordinates->robots[1][i].y;
        worldModel.oppRobots[i].vel = (worldModel.oppRobots[i].pos - lastWorldModel.oppRobots[i].pos) * 20;// m/s(50 ms each frame)
        worldModel.oppRobots[i].active = f.opt_coordinates->robots[1][i].active;
        worldModel.oppRobots[i].theta = rcsc::AngleDeg::normalize_angle(f.opt_coordinates->robots[1][i].th * rcsc::AngleDeg::RAD2DEG);
        worldModel.oppRobots[i].angularVel = rcsc::AngleDeg::normalize_angle(worldModel.oppRobots[i].theta - lastWorldModel.oppRobots[i].theta)*20;// deg/s(50 ms each frame)
    }
    //ball
    worldModel.ball.pos.x = f.opt_coordinates->ball.x;
    worldModel.ball.pos.y = f.opt_coordinates->ball.y;
    worldModel.ball.vel = (worldModel.ball.pos - lastWorldModel.ball.pos) * 20;// m/s(50 ms each frame)
    worldModel.ball.active = true;
    worldModel.ball.theta = 0;
    worldModel.ball.angularVel = 0;
}

