//
// Created by Víctor on 20/06/2022.
//

#ifndef H2O_MASTER_COMMSERVER_H
#define H2O_MASTER_COMMSERVER_H

#include "Communications.h"

class ComManager
{
public:
    ComManager(HardwareSerial* serial);
    void messageManager(); // Todo check if this should be private
    void commSetup();
    void commLoop();
    bool sendMessage(const char* payload);

private:
    HardwareSerial* serial;
};

#include "ComManager.cpp"

#endif //H2O_MASTER_COMMSERVER_H
