#ifndef PARSIAN_MYPROTOBUF_H
#define PARSIAN_MYPROTOBUF_H

#ifndef USE_PROTO
    void sendWorldModelMessage(){}
#else

#include <iostream>
#include "messages_parsian_worldmodel.pb.h"
void sendWorldModelMessage()
{
    std::cout << "proto" << std::endl;
}



#endif //USE_PROTO

#endif //PARSIAN_MYPROTOBUF_H
