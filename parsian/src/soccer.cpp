#include "soccer.h"
#include "geom/vector_2d.h"
Soccer::Soccer(std::string server_ip, std::size_t port, std::string realm, std::string key, std::string datapath)
        : ai_base(std::move(server_ip), port, std::move(realm), std::move(key), std::move(datapath))
{
    std::cout << "PARSIAN TEAM start" << std::endl;
    gameState = GameState::playOn;

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
    //std::cout << "game state: " << gameStateToString(gameState) << std::endl;
    //test geom
    rcsc::Vector2D pos{2, 3};
    std::cout << pos.length() << std::endl;



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


