//
// Created by Víctor on 20/06/2022.
//

#include "CommServer.h"

CommServer::CommServer(HardwareSerial* serial)
{
    this->serial = serial;
}

void CommServer::messageManager()
{
    if(serial->available())
    {
        char bufferSerial[MAXMSGSIZE];
        char variableId[32];
        char functionId[32];
        char value[32];
        Communications::getMessage(bufferSerial,serial);
        switch (bufferSerial[0])
        {
            case ID_REQUESTMESSAGE:
                Communications::extractRequestMessage(bufferSerial,variableId,functionId);
                break;
            case ID_REQUESTANSWERMESSAGE:
                Communications::extractRequestAnswerMessage(bufferSerial,variableId,value,functionId);
                break;
            case ID_SENDMESSAGE:
                Communications::extractSendMessage(bufferSerial,variableId,value);
                break;
            default:
                debug(F("Unknown message: ")+bufferSerial);
        }
    }
}

void CommServer::commLoop() // TODO server function
{

}

void CommServer::commSetup() // TODO start communications
{

}

bool CommServer::sendMessage(const char *payload)
{
    return Communications::sendMessage(payload,serial);
}