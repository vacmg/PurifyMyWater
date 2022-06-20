//
// Created by Víctor on 20/06/2022.
//

#ifndef H2O_MASTER_COMMSERVER_H
#define H2O_MASTER_COMMSERVER_H

#include "Communications.h"

class CommServer
{
public:
    CommServer(HardwareSerial* serial);
    void messageManager(); // Todo check if this should be private
    void commSetup();
    void commLoop();
    bool sendMessage(const char* payload);

private:
    HardwareSerial* serial;
};



#endif //H2O_MASTER_COMMSERVER_H
