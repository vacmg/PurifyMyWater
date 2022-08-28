//
// Created by Víctor on 20/06/2022.
//

#include "ComManager.h"

ComManager::ComManager(HardwareSerial* serial, void (*sendMessageHandler)(enum VariableIDs variableID, char* value), void (*requestMessageHandler)(enum VariableIDs variableID, enum FunctionIDs functionID, byte step), void (*requestAnswerMessageHandler)(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step))
{
    this->serial = serial;
    this->enabled = false;
    this->sendMessageHandler = sendMessageHandler;
    this->requestMessageHandler = requestMessageHandler;
    this->requestAnswerMessageHandler = requestAnswerMessageHandler;
}

bool ComManager::commSetup()
{
    if(!enabled)
    {
        serial->begin(COMMANAGERBAUDRATE);
        delay(100);
        flush();
        delay(50);
        if(doHandshake())
        {
            enabled = true;
            debug(F("Successful handshake\n"));
            return true;
        }
        else
        {
            serial->end();
            return false;
        }
    }
    return true;
}

bool ComManager::commDisabler()
{
    if(enabled)
    {
        serial->end();
        enabled = false;
    }
    return true;
}

bool ComManager::checkCompatibleVersions(char* localVersion, char* otherVersion)
{
    debug(F("localVersion:      "));debug(localVersion);debug('\n');
    debug(F("otherVersion:      "));debug(otherVersion);debug('\n');
    localVersion = strtok(localVersion,"."); // Get localVersion major version
    otherVersion = strtok(otherVersion,"."); // Get otherVersion major version
    /*debug(F("localMajorVersion: "));debug(localVersion);debug('\n');
    debug(F("otherMajorVersion: "));debug(otherVersion);debug('\n');*/
    bool res = strcmp(localVersion,otherVersion)==0; // Compare major versions
    if(!res)
    {
        debug(F("Handshake Error: MCUs are incompatible\n"));
        dataStorage.data.currentError = MCUsIncompatibleVersionError;
    }

    return res;
}

// This function performs the handshake to ensure the connection is working properly & both MCUs have compatible software
// The handshake consists of retrieving other's version string & ensuring both have the same major version
// During the handshake, the system is able to answer the other MCU handshake request
bool ComManager::doHandshake()
{
    char ourVersion[MAXVERSIONSIZE];
    char otherVersion[MAXVERSIONSIZE];
    strcpy_P(ourVersion,VERSION);
    char okMsg[3];
    char ourVersionMsg[MAXVERSIONSIZE+2];

    if(Communications::createSendMessage(ourVersionMsg,VERSION_ID,ourVersion)
    && Communications::createSendMessage(okMsg,OK_CMD,""))
    {
        debug(F("Performing handshake...\n"));
        bool okSent = false, okReceived = false;
        char receivedMsg[MAXMSGSIZE] = "";
        char receivedData[MAXVERSIONSIZE] = "";
        unsigned long handshakeMillis = millis();

        while ((!okSent || !okReceived) && handshakeMillis+HANDSHAKETIMEOUT>millis())
        {
            Communications::sendQuickMessage(ourVersionMsg, serial);
            while (Communications::getQuickMessage(receivedMsg, serial))
            {
                if (receivedMsg[0] == SENDMESSAGE_ID)
                {
                    enum VariableIDs cmdID;
                    if (Communications::extractSendMessage(receivedMsg,&cmdID,receivedData))
                    {
                        if(cmdID == VERSION_ID)
                        {
                            //debug(F("OK Sent\n"));
                            strcpy(otherVersion,receivedData);
                            Communications::sendQuickMessage(okMsg, serial);
                            okSent = true;
                        }
                        else if(cmdID == OK_CMD)
                        {
                            //debug(F("OK Received\n"));
                            okReceived = true;
                        }
                    }
                }
                //debug(F("okSent: "));debug(okSent);debug('\n');
                //debug(F("okReceived: "));debug(okReceived);debug(F("\n\n"));
            }
            delay(250);
        }
        flush();
        if(okReceived && okSent)
        {
            //debug(F("Both MCUs have other's version\n"));
            return checkCompatibleVersions(ourVersion,otherVersion);
        }
        else
        {
            debug(F("Handshake Error: Timeout\n"));
        }
    }
    else
    {
        debug(F("Handshake Error: Cannot create messages\n"));
    }
    dataStorage.data.currentError = HandshakeError;
    return false;
}

void ComManager::commLoop()
{
    if(enabled && serial->available())
    {
        char serialBuffer[MAXMSGSIZE] = "";
        enum VariableIDs variableID;
        enum FunctionIDs functionID;
        byte step;
        char value[MAXVALUESIZE];
        if(Communications::getMessage(serialBuffer,serial))
        {
            switch (serialBuffer[0])
            {
                case REQUESTMESSAGE_ID:
                    Communications::extractRequestMessage(serialBuffer,&variableID,&functionID,&step);
                    requestMessageHandler(variableID,functionID,step);
                    debug(F("REQUESTMESSAGE\n"));
                    break;
                case REQUESTANSWERMESSAGE_ID:
                    Communications::extractRequestAnswerMessage(serialBuffer,&variableID,value,&functionID,&step);
                    requestAnswerMessageHandler(variableID,value,functionID,step);
                    debug(F("REQUESTANSWERMESSAGE\n"));
                    break;
                case SENDMESSAGE_ID:
                    Communications::extractSendMessage(serialBuffer,&variableID,value);
                    sendMessageHandler(variableID,value);
                    debug(F("SENDMESSAGE\n"));
                    break;
                default:
                    debug(F("Unknown message: "));debug(serialBuffer);debug('\n');
            }
        }
    }
}


bool ComManager::sendMessage(const char *payload)
{
    return enabled && Communications::sendMessage(payload,serial);
}

bool ComManager::sendQuickMessage(const char* payload)
{
    return enabled && Communications::sendQuickMessage(payload,serial) && await();
}

bool ComManager::flush()
{
    return enabled && Communications::flush(serial);
}
bool ComManager::await()
{
    return enabled && Communications::await(serial);
}

bool ComManager::isEnabled()
{
    return enabled;
}

int ComManager::dataAvailable()
{
    return enabled?serial->available():0;
}

HardwareSerial* ComManager::getSerial()
{
    return serial;
}
