//
// Created by Víctor on 20/06/2022.
//

#ifndef H2O_MASTER_COMMSERVER_H
#define H2O_MASTER_COMMSERVER_H

#include "Communications.h"
#include "../Shared/SharedData.h"

class ComManager
{
public:
    explicit ComManager(HardwareSerial* serial);
    void commSetup();
    void commLoop();
    bool sendMessage(const char* payload);

private:
    HardwareSerial* serial;

    void messageManager();
    void sendMessageHandler(char* buffer);
    void requestMessageHandler(char* buffer);
    void requestAnswerMessageHandler(char* buffer);
};

#include "ComManager.cpp"

#endif //H2O_MASTER_COMMSERVER_H
