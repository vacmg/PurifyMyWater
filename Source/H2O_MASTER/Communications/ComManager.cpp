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
        char bufferSerial[MAXPAYLOADSIZE] = "";
        char variableId[32] = "";
        char functionId[32] = "";
        char value[32] = "";
        Communications::getMessage(bufferSerial,serial);
        switch (bufferSerial[0])
        {
            case REQUESTMESSAGE_ID:
                Communications::extractRequestMessage(bufferSerial,variableId,functionId);
				debug(F("REQUESTMESSAGE\n"));
                break;
            case REQUESTANSWERMESSAGE_ID:
                Communications::extractRequestAnswerMessage(bufferSerial,variableId,value,functionId);
				debug(F("REQUESTANSWERMESSAGE\n"));
                break;
            case SENDMESSAGE_ID:
                Communications::extractSendMessage(bufferSerial,variableId,value);
				debug(F("SENDMESSAGE\n"));
                break;
            default:
                debug(F("Unknown message: "));debug(bufferSerial);debug('\n');
        }
		debug(F("variableId: "));debug(variableId);
		debug(F("\nfunctionId: "));debug(functionId);
		debug(F("\nvalue: "));debug(value);debug('\n');
    }
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