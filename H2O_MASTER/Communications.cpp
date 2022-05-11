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
#define ID_REQUESTMESSAGE 1
#define ID_REQUESTMESSAGE 2
#define ID_SENDMESSAGE 3
#define SEPARATOR ","

char bufferSerial[MAXMSGSIZE];
void messageManager(HardwareSerial* serial){
    if(serial->available())
    {
        getMessage(bufferSerial,serial);

    }
}

bool createRequestMessage(char* buffer, const char* variableID, const char* funcionID)
{
    if(variableID == NULL || buffer == NULL || funcionID == NULL)
        return false;
    buffer[0] = ID_REQUESTMESSAGE;
    strcat(buffer,variableID);
    strcat(buffer,SEPARATOR);
    strcat(buffer,funcionID);
    return true
}

bool extractRequestMessage(const char* buffer, char* variableID, char* funcionID)
{
    if(buffer == NULL || variableID == NULL || funcionID == NULL)
        return false;
    strcpy(variableID,strtok(&buffer[1],SEPARATOR));
    strcpy(funcionID,strtok(NULL,SEPARATOR);
    return true
}

bool createSendMessage(char* buffer, byte variableID, const char* valor)
{
    if(valor == NULL || buffer == NULL)
        return false;
    buffer[0] = ID_SENDMESSAGE; // ID sendMessage
    buffer[1] = variableID;
    strcpy(&buffer[2], valor);
    return true;
}

bool extractSendMessage(const char* buffer, byte* variableID, char* valor)
{
    if(valor == NULL || buffer == NULL)
        return false;
    *variableID = buffer[1];
    strcpy(valor, &buffer[2]);

bool createRequestAnswerMessage(char* buffer, const char* idVariable, const char* value, const char* idFunction)
{
    if (buffer == NULL || value == NULL || idVariable == NULL || idFunction == NULL)
        return false;

    buffer[0] = ID_REQUESTMESSAGE;
    strcat(buffer, SEPARATOR);
    strcat(buffer, idVariable);
    strcat(buffer, SEPARATOR);
    strcat(buffer, value);
    strcat(buffer, SEPARATOR);
    strcat(buffer, idFunction);

    return true;
}

bool extractRequestAnswerMessage(char* buffer, char* idVariable, char* value, char* idFunction)
{
    if (buffer == NULL || value == NULL || idVariable == NULL || idFunction == NULL)
        return false;

    strcpy(idVariable, strtok(buffer, SEPARATOR));
    strcpy(value, strtok(NULL, SEPARATOR));
    strcpy(idFunction, strtok(NULL, SEPARATOR));
    return true;
}

bool sendMessage(const char* payload, HardwareSerial* serial)
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

bool getMessage(char* message, HardwareSerial* serial)
{
    delay(100);
    serial->readBytesUntil('\n',message,MAXRAWMSGSIZE); // [CRC][size][payload]
    flush(serial);

    if (verifyMessage(message)) // if crc match expected crc
    {
        serial->write(ACK);
        return true;
    }
    return false;
}

bool verifyMessage(char* message)
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
byte CRC8(const byte* data, size_t dataLength)
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
void flush(HardwareSerial* serial)
{
    while (serial->available())
    {
        serial->read();
    }
}
