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
            debug(F("ComManager: Successful handshake\n"));
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
    debug(F("ComManager: localVersion:      "));debug(localVersion);debug('\n');
    debug(F("ComManager: otherVersion:      "));debug(otherVersion);debug('\n');
    localVersion = strtok(localVersion,"."); // Get localVersion major version
    otherVersion = strtok(otherVersion,"."); // Get otherVersion major version
    /*debug(F("localMajorVersion: "));debug(localVersion);debug('\n');
    debug(F("otherMajorVersion: "));debug(otherVersion);debug('\n');*/
    bool res = strcmp(localVersion,otherVersion)==0; // Compare major versions
    if(!res)
    {
        debug(F("ComManager: Handshake Error: MCUs are incompatible\n"));
        changeError(MCUsIncompatibleVersionError);
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
    char ourVersionMsg[MAXVERSIONSIZE+2]; // 1(Message_ID)+1(variableID)

    if(Communications::createSendMessage(ourVersionMsg,VERSION_ID,ourVersion)
    && Communications::createSendMessage(okMsg,OK_CMD,""))
    {
        debug(F("ComManager: Performing handshake...\n"));
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
            debug(F("ComManager: Handshake Error: Timeout\n"));
        }
    }
    else
    {
        debug(F("ComManager: Handshake Error: Cannot create messages\n"));
    }
    changeError(HandshakeError);
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
                    debug(F("ComManager: RequestMessage received\n"));
                    requestMessageHandler(variableID,functionID,step);
                    break;
                case REQUESTANSWERMESSAGE_ID:
                    Communications::extractRequestAnswerMessage(serialBuffer,&variableID,value,&functionID,&step);
                    debug(F("ComManager: RequestAnswerMessage received\n"));
                    requestAnswerMessageHandler(variableID,value,functionID,step);
                    break;
                case SENDMESSAGE_ID:
                    Communications::extractSendMessage(serialBuffer,&variableID,value);
                    debug(F("ComManager: SendMessage received\n"));
                    sendMessageHandler(variableID,value);
                    break;
                default:
                    debug(F("ComManager: Unknown message: "));debug(serialBuffer);debug('\n');
            }
        }
    }
}

bool ComManager::sendMessage(const char *payload)
{
    if(enabled)
    {
        if(Communications::sendMessage(payload,serial))
            return true;
        else
        {
            changeError(DestinationMCUNotRespondingError);
        }
    }
}


void ComManager::setSendMessageHandler(void (*sendMessageHandler)(enum VariableIDs variableID, char* value))
{
    this->sendMessageHandler = sendMessageHandler;
}
void ComManager::setRequestMessageHandler(void (*requestMessageHandler)(enum VariableIDs variableID, enum FunctionIDs functionID, byte step))
{
    this->requestMessageHandler = requestMessageHandler;
}
void ComManager::setRequestAnswerMessageHandler(void (*requestAnswerMessageHandler)(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step))
{
    this->requestAnswerMessageHandler = requestAnswerMessageHandler;
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

bool ComManager::isEnabled() const
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
