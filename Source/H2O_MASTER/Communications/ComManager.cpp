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
        if(doHandShake())
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

bool ComManager::doHandShake()
{
    
}

void ComManager::commLoop()
{
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
    }
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
