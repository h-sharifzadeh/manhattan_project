#ifndef PARSIAN_MYPROTOBUF_H
#define PARSIAN_MYPROTOBUF_H

#ifndef USE_PROTO
    void sendWorldModelMessage(const WorldModel& worldmodel){}
#else

#include <iostream>
#include "messages_parsian_worldmodel.pb.h"
WorldModelProto wm{};
void sendWorldModelMessage(const WorldModel& worldmodel)
{

}



#endif //USE_PROTO

#endif //PARSIAN_MYPROTOBUF_H
