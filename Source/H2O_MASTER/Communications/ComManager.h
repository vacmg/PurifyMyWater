//
// Created by Víctor on 20/06/2022.
//

#ifndef H2O_MASTER_COMMANAGER_H
#define H2O_MASTER_COMMANAGER_H

#include "Communications.h"
#include "../Shared/SharedData.h"

#define COMMANAGERBAUDRATE 9600
#define HANDSHAKETIMEOUT 5000

class ComManager
{
public:
    ComManager(HardwareSerial* serial, void (*sendMessageHandler)(enum VariableIDs variableID, char* value), void (*requestMessageHandler)(enum VariableIDs variableID, enum FunctionIDs functionID, byte step), void (*requestAnswerMessageHandler)(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step));
    bool commSetup();
    bool commDisabler();
    void commLoop();
    bool sendMessage(const char* payload);
    bool sendQuickMessage(const char* payload);

    bool flush();
    bool await();

private:
    HardwareSerial* serial;
    bool enabled;
    void (*sendMessageHandler)(enum VariableIDs variableID, char* value);
    void (*requestMessageHandler)(enum VariableIDs variableID, enum FunctionIDs functionID, byte step);
    void (*requestAnswerMessageHandler)(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step);

    bool checkCompatibleVersions(char* v1, char* v2);
    bool doHandshake();


};

#include "ComManager.cpp"

#endif //H2O_MASTER_COMMANAGER_H
