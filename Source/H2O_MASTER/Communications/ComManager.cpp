//
// Created by Víctor on 20/06/2022.
//

#include "ComManager.h"

// TODO remove this
#define debug(data) Serial.println(data)

ComManager::ComManager(HardwareSerial* serial)
{
    this->serial = serial;
}

void ComManager::messageManager()
{
    if(serial->available())
    {
        char serialBuffer[MAXPAYLOADSIZE] = "";
        char variableId[32] = "";
        char functionId[32] = "";
        char value[32] = "";
        Communications::getMessage(serialBuffer,serial);
        switch (serialBuffer[0])
        {
            case REQUESTMESSAGE_ID:
                requestMessageHandler(serialBuffer);
				debug(F("REQUESTMESSAGE\n"));
                break;
            case REQUESTANSWERMESSAGE_ID:
                Communications::extractRequestAnswerMessage(serialBuffer,variableId,value,functionId);
				debug(F("REQUESTANSWERMESSAGE\n"));
                break;
            case SENDMESSAGE_ID:
                Communications::extractSendMessage(serialBuffer,variableId,value);
				debug(F("SENDMESSAGE\n"));
                break;
            default:
                debug(F("Unknown message: "));debug(serialBuffer);debug('\n');
        }
		debug(F("variableId: "));debug(variableId);
		debug(F("\nfunctionId: "));debug(functionId);
		debug(F("\nvalue: "));debug(value);debug('\n');
    }
}

void sendMessageHandler(char* buffer)
{

}

void requestMessageHandler(char* buffer)
{
    //Communications::extractRequestMessage(buffer,variableId,functionId);
}

void requestAnswerMessageHandler(char* buffer)
{

}

void ComManager::commLoop() // TODO server function
{

}

void ComManager::commSetup() // TODO start communications
{

}

bool ComManager::sendMessage(const char *payload)
{
    return Communications::sendMessage(payload,serial);
}