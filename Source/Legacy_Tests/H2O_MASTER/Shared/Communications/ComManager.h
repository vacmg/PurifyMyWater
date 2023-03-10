//
// Created by Víctor on 20/06/2022.
//

#ifndef H2O_COMMANAGER_H
#define H2O_COMMANAGER_H

#include "Communications.h"
#include "../SharedData.h"

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

    void setSendMessageHandler(void (*sendMessageHandler)(enum VariableIDs variableID, char* value));
    void setRequestMessageHandler(void (*requestMessageHandler)(enum VariableIDs variableID, enum FunctionIDs functionID, byte step));
    void setRequestAnswerMessageHandler(void (*requestAnswerMessageHandler)(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step));
    bool flush();
    bool await();
    bool isEnabled() const;
    int dataAvailable();
    HardwareSerial* getSerial();

private:
    HardwareSerial* serial;
    bool enabled;
    void (*sendMessageHandler)(enum VariableIDs variableID, char* value);
    void (*requestMessageHandler)(enum VariableIDs variableID, enum FunctionIDs functionID, byte step);
    void (*requestAnswerMessageHandler)(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step);

    static bool checkCompatibleVersions(char* localVersion, char* otherVersion);
    bool doHandshake();


};

#include "ComManager.cpp"

#endif //H2O_COMMANAGER_H
