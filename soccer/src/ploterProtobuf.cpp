//
// Created by parsian-ai on 10/10/19.
//

#include "ploterProtobuf.h"

WorldModelProto* twm = new(WorldModelProto);
int thisSocket;
struct sockaddr_in destination;

void initServer()
{
    destination.sin_family = AF_INET;
    thisSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (thisSocket < 0)
        std::cerr << "Socket Creation FAILED!" << std::endl;

    destination.sin_port = htons(13375);
    destination.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(thisSocket,(struct sockaddr *)&destination,sizeof(destination))!=0)
    {
        std::cerr << "Socket Connection FAILED!" << std::endl;
        if (thisSocket) close(thisSocket);
    }
    std::cout << "Socket Connection SUCCEED" << std::endl;
    //close(thisSocket)
}

void vec2D2vec2D(const rcsc::Vector2D& v1, Vector2DProto* v2) {
    v2->set_x(v1.getX());
    v2->set_y(v1.getY());
}

void fillMessage(const WorldModel& worldmodel)
{
    delete twm;
    twm = new(WorldModelProto);
    twm->set_blue(false);
    twm->set_gamestate(GameStateProto::PlayOn);
    twm->set_mode("kianMode");
    MovingObjectProto* moball = twm->mutable_ball();
    moball->set_id(0);
    moball->set_direction(0);
    moball->set_angulevelocity(0);
    vec2D2vec2D(worldmodel.ball.pos, moball->mutable_pos());
    vec2D2vec2D(worldmodel.ball.vel, moball->mutable_vel());
    vec2D2vec2D(rcsc::Vector2D{0, 0}, moball->mutable_acc());
    for (int i = 0; i < worldmodel.ourRobots.size(); i++) {
        MovingObjectProto* ourR = twm->add_our_robots();
        const Robot& wor = worldmodel.ourRobots[i];
        ourR->set_id(wor.id);
        ourR->set_angulevelocity(wor.angularVel);
        ourR->set_direction(wor.theta);
        vec2D2vec2D(wor.pos, ourR->mutable_pos());
        vec2D2vec2D(wor.vel, ourR->mutable_vel());
        vec2D2vec2D(rcsc::Vector2D{0, 0}, ourR->mutable_acc());

        MovingObjectProto* oppR = twm->add_opp_robots();
        const Robot& wopr = worldmodel.oppRobots[i];
        oppR->set_id(wopr.id);
        oppR->set_angulevelocity(wopr.angularVel);
        oppR->set_direction(wopr.theta);
        vec2D2vec2D(wopr.pos, oppR->mutable_pos());
        vec2D2vec2D(wopr.vel, oppR->mutable_vel());
        vec2D2vec2D(rcsc::Vector2D{0, 0}, oppR->mutable_acc());

    }
}

void sendWorldModelMessage(const WorldModel& worldmodel)
{
    fillMessage(worldmodel);
    std::string str;
    str.resize(twm->ByteSize());
    if (twm->SerializePartialToString(&str))
    {
        //send data over network
        send(thisSocket, str.c_str(), str.size(), 0);
    }
}
