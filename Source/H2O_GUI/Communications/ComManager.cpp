//
// Created by Víctor on 20/06/2022.
//

#include "ComManager.h"

ComManager::ComManager(HardwareSerial* serial)
{
    this->serial = serial;
    this->enabled = false;
}

bool ComManager::commSetup() // TODO start communications
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
    else return true;
}

bool ComManager::commDisabler() // TODO end communications
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
        data.currentError = MCUsIncompatibleVersionError;
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
            sendQuickMessage(ourVersionMsg);
            while (Communications::getQuickMessage(receivedMsg,serial))
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
                            sendQuickMessage(okMsg);
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
    data.currentError = HandshakeError;
    return false;
}

void ComManager::commLoop()
{/*
    if(enabled && serial->available())
    {
        char serialBuffer[MAXPAYLOADSIZE] = "";
        if(Communications::getMessage(serialBuffer,serial))
        {
            switch (serialBuffer[0])
            {
                case REQUESTMESSAGE_ID:
                    requestMessageMasterHandler(serialBuffer);
                    debug(F("REQUESTMESSAGE\n"));
                    break;
                case REQUESTANSWERMESSAGE_ID:
                    requestAnswerMessageMasterHandler(serialBuffer);
                    debug(F("REQUESTANSWERMESSAGE\n"));
                    break;
                case SENDMESSAGE_ID:
                    sendMessageMasterHandler(serialBuffer);
                    debug(F("SENDMESSAGE\n"));
                    break;
                default:
                    debug(F("Unknown message: "));debug(serialBuffer);debug('\n');
            }
        }
    }*/
}

void ComManager::sendMessageMasterHandler(char* buffer)
{

}

void ComManager::requestMessageMasterHandler(char* buffer)
{
    //Communications::extractRequestMessage(buffer,variableId,functionId);
}

void ComManager::requestAnswerMessageMasterHandler(char* buffer)
{

}

bool ComManager::sendMessage(const char *payload)
{
    return Communications::sendMessage(payload,serial);
}

bool ComManager::sendQuickMessage(const char* payload)
{
    return Communications::sendQuickMessage(payload,serial) && await();
}

bool ComManager::flush()
{
    return Communications::flush(serial);
}
bool ComManager::await()
{
    return Communications::await(serial);
}
