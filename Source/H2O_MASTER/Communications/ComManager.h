//
// Created by Víctor on 20/06/2022.
//

#ifndef H2O_MASTER_COMMANAGER_H
#define H2O_MASTER_COMMANAGER_H

#include "Communications.h"
#include "../Shared/SharedData.h"

#define COMMANAGERBAUDRATE 9600

class ComManager
{
public:
    explicit ComManager(HardwareSerial* serial);
    bool commSetup();
    bool commDisabler();
    void commLoop();
    bool sendMessage(const char* payload);

private:
    HardwareSerial* serial;
    bool enabled;

    bool doHandShake();
    void sendMessageMasterHandler(char* buffer);
    void requestMessageMasterHandler(char* buffer);
    void requestAnswerMessageMasterHandler(char* buffer);
};

#include "ComManager.cpp"

#endif //H2O_MASTER_COMMANAGER_H
