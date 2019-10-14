//
// Created by parsian-ai on 10/10/19.
//

#ifndef PARSIAN_PLOTERPROTOBUF_H
#define PARSIAN_PLOTERPROTOBUF_H

#ifndef PARSIAN_MYPROTOBUF_H
#define PARSIAN_MYPROTOBUF_H

#ifndef USE_DEBUG
void sendWorldModelMessage(const WorldModel& worldmodel){}
    void initServer(){}
#else

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>
#include "messages_parsian_worldmodel.pb.h"
#include "worldmodel.h"

void initServer();

void vec2D2vec2D(const rcsc::Vector2D& v1, Vector2DProto* v2) ;

void fillMessage(const WorldModel* worldmodel);
void sendWorldModelMessage(const WorldModel* worldmodel);

#endif //USE_PROTO

#endif //PARSIAN_MYPROTOBUF_H

#endif //PARSIAN_PLOTERPROTOBUF_H
