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
        if(doHandshake())
        {
            enabled = true;
        }
        else
            serial->end();
    }
}

bool ComManager::commDisabler() // TODO end communications
{
    if(enabled)
    {
        serial->end();
        enabled = false;
    }
}

bool ComManager::checkCompatibleVersions(char* v1, char* v2)
{
    v1 = strtok(v1,"."); // Get v1 major version
    v2 = strtok(v2,"."); // Get v2 major version
    return strcmp(v1,v2)==0; // Compare major versions
}

// This function is a little implementation of commLoop() which only handles handshake communication
// It returns 0 if nothing happened, 1 if other's version has arrived, and -1 if other's request for our version have arrived
char ComManager::handshakeLoop(char* message, char* version, char* otherVersion)
{
    if(serial->available())
    {
        if(Communications::getQuickMessage(message,serial)) // If a message is received
        {
            enum VariableIDs variableID;
            enum FunctionIDs functionID;
            byte step;
            switch (message[0])
            {
                case REQUESTANSWERMESSAGE_ID: // If it is the answer of our request, return 1
                    if(Communications::extractRequestAnswerMessage(message,&variableID,otherVersion,&functionID,&step))
                    {
                        if(variableID==VERSION_ID && functionID == Handshake_ID)
                        {
                            return 1;
                        }
                    }
                    break;
                case REQUESTMESSAGE_ID: // if it is the request of the other MCU, proccess the request and return -1
                    if(Communications::extractRequestMessage(message,&variableID,&functionID,&step))
                    {
                        if(variableID==VERSION_ID && functionID == Handshake_ID)
                        {
                            if(Communications::createRequestAnswerMessage(message,variableID,version,functionID,step))
                                if(sendQuickMessage(message))
                                    return -1;
                        }
                    }
            }
        }
    }
    return 0;
}

// This function performs the handshake to ensure the connection is working properly & both MCUs have compatible software
// The handshake consists of retrieving other's version string & ensuring both have the same major version
// During the handshake, the system is able to answer the other MCU handshake request
bool ComManager::doHandshake()
{
    char message[MAXPAYLOADSIZE];
    if(Communications::createRequestMessage(message,VERSION_ID,Handshake_ID,1))
    {
        sendQuickMessage(message); // Send handshake request
        //TODO modificar funcion para no colapsar al enviar a la vez 2 mensajes (usar los quick)

        // Get VERSION to RAM (it is stored in PROGMEM)
        char version[MAXVERSIONSIZE];
        strcpy_P(version,VERSION);
        char otherVersion[MAXVERSIONSIZE]; // Reserve space for the other version string

        bool requestAnswered = false;
        bool versionSent = false;
        unsigned long handshakeMillis = millis();
        while ((!requestAnswered || !versionSent) && handshakeMillis+HANDSHAKETIMEOUT<millis()) // Check for answer or timeout
        {
            char res = handshakeLoop(message,version,otherVersion); // Get the other's version & send our version
            if(res == 1)
            {
                requestAnswered = true; // We have the other's version
            }
            else if(res == -1)
            {
                versionSent = true; // The other MCU has our version
            }
        }
        if(requestAnswered && versionSent) // if both have both versions, that check should give the same result
            return checkCompatibleVersions(otherVersion,version);
    }
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
    return Communications::sendQuickMessage(payload,serial);
}
