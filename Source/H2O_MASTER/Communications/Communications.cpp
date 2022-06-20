//
// Created by Víctor, Andrés and Gabriel on 05/05/2022.
//

#include "Communications.h"

/*
 * [CRC][size][payload]\n
 * CRC: CRC8 code of [size][payload]
 * size: size in bytes of [size]+[payload]
 * payload: useful data of the message
 * \n: terminator character
 */

// Application layer
bool Communications::createSendMessage(char* payload, byte variableID, const char* value)
{
    if(value == NULL || payload == NULL)
        return false;
    payload[0] = ID_SENDMESSAGE; // ID sendMessage
    payload[1] = variableID;
    strcpy(&payload[2], value);
    return true;
}

bool Communications::extractSendMessage(const char* payload, char* variableID, char* value)
{
    if (value == NULL || payload == NULL)
        return false;
    *variableID = payload[1];
    strcpy(value, &payload[2]);
}

bool Communications::createRequestMessage(char* payload, const char* variableID, const char* functionID)
{
    if(variableID == NULL || payload == NULL || functionID == NULL)
        return false;
    payload[0] = ID_REQUESTMESSAGE;
    strcat(payload,variableID);
    strcat(payload,SEPARATOR);
    strcat(payload,functionID);
    return true;
}

bool Communications::extractRequestMessage(char* payload, char* variableID, char* functionID)
{
    if(payload == NULL || variableID == NULL || functionID == NULL)
        return false;
    strcpy(variableID,strtok(&payload[1],SEPARATOR));
    strcpy(functionID,strtok(NULL,SEPARATOR));
    return true;
}

bool Communications::createRequestAnswerMessage(char* payload, const char* variableID, const char* value, const char* functionID)
{
    if (payload == NULL || value == NULL || variableID == NULL || functionID == NULL)
        return false;

    payload[0] = ID_REQUESTANSWERMESSAGE;
    strcat(payload, SEPARATOR);
    strcat(payload, variableID);
    strcat(payload, SEPARATOR);
    strcat(payload, value);
    strcat(payload, SEPARATOR);
    strcat(payload, functionID);
    return true;
}

bool Communications::extractRequestAnswerMessage(char* payload, char* variableID, char* value, char* functionID)
{
    if (payload == NULL || value == NULL || variableID == NULL || functionID == NULL)
        return false;

    strcpy(variableID, strtok(payload, SEPARATOR));
    strcpy(value, strtok(NULL, SEPARATOR));
    strcpy(functionID, strtok(NULL, SEPARATOR));
    return true;
}


// Link layer
bool Communications::sendMessage(const char* payload, HardwareSerial* serial)
{
    byte payloadLength = strlen(payload);
    if(payloadLength>MAXMSGSIZE)
    {
        debug(Message(F("Payload exceeded maximum message size: ")+payloadLength+F(" > ")+MAXMSGSIZE));
    }
    char message[MAXRAWMSGSIZE];
    message[1] = payloadLength+1; // set size of the message
    strcpy(&message[2],payload); // copy payload to message
    strcat(message,"\n"); // Add \n terminator
    message[0] = CRC8((byte*)&message[1],message[1]); // set CRC of the message

    bool successfulSend = false;
    for(byte i = 0; !successfulSend && i<MAXMSGRETRIES; i++)
    {
        serial->write(message,payloadLength+3);//[CRC][size][payload]\n
        unsigned long startTime = millis();
        while (!successfulSend && millis()-startTime<MSGTIMEOUT)
        {
            successfulSend = serial->available() && serial->read()==ACK;
        }
        flush(serial);
    }
    return successfulSend;
}

bool Communications::getMessage(char* payload, HardwareSerial* serial)
{
    delay(100);
    serial->readBytesUntil('\n',payload,MAXRAWMSGSIZE); // [CRC][size][payload]
    flush(serial);

    if (verifyMessage(payload)) // if crc match expected crc
    {
        serial->write(ACK);
        return true;
    }
    return false;
}

bool Communications::verifyMessage(char* message)
{
    byte originCRC = message[0]; // Origin CRC code
    byte size = message[1]; // size of [tam]+[message]
    byte realCRC = CRC8((byte*) &message[1],size); // get CRC8 of [tam][message]
    for(byte i = 0; i<size;i++)
    {
        message[i] = message [i+2];
    }
    return originCRC==realCRC;
}

//This function returns a CRC8 Checksum code from an array of any size
//CRC-8 Checksum - based on the CRC8 formulas by Dallas/Maxim
//code released under the terms of the GNU GPL 3.0 license
byte Communications::CRC8(const byte* data, size_t dataLength)
{
    byte crc = 0x00;
    while (dataLength--)
    {
        byte extract = *data++;
        for (byte tempI = 8; tempI; tempI--)
        {
            byte sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if (sum)
            {
                crc ^= 0x8C;
            }
            extract >>= 1;
        }
    }
    return crc;
}

// This function flushes an input HardwareSerial and discards all data on the input buffer
void Communications::flush(HardwareSerial* serial)
{
    while (serial->available())
    {
        serial->read();
    }
}
