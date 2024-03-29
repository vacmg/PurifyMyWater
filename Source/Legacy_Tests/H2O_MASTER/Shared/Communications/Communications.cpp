//
// Created by Víctor, Andrés and Gabriel on 05/05/2022.
//

#include "Communications.h"

/*
 * [CRC][size][payload]
 * CRC: CRC8 code of [size][payload]
 * size: size in bytes of [size]+[payload]
 * payload: useful data of the message
 */

// Application layer

// This function puts information together to create a sendMessage payload
bool Communications::createSendMessage(char* payload, enum VariableIDs variableID, const char* value)
{
    if(value == nullptr || strlen(value)>MAXVALUESIZE-1 || payload == nullptr)
        return false;
    payload[0] = SENDMESSAGE_ID; // ID sendMessage
    payload[1] = variableID;
    payload[2] = '\0'; // ensure strcat works (it will be replaced by strcat)
    strcat(payload, value);
    return true;
}

// This function extracts information from a sendMessage payload
bool Communications::extractSendMessage(const char* payload, enum VariableIDs* variableID, char* value)
{
    if (value == nullptr || payload == nullptr || variableID == nullptr)
        return false;
    *variableID = (VariableIDs)payload[1];
    strcpy(value,&payload[2]);
    return true;
}

// This function puts information together to create a requestAnswerMessage payload
bool Communications::createRequestAnswerMessage(char* payload, enum VariableIDs variableID, const char* value, enum FunctionIDs functionID, byte step)
{
    if (payload == nullptr || value == nullptr || strlen(value)>MAXVALUESIZE-1 || step<1)
        return false;

    payload[0] = REQUESTANSWERMESSAGE_ID;
    payload[1] = variableID;
    payload[2] = functionID;
    payload[3] = step;
    payload[4] = '\0'; // ensure strcat works (it will be replaced by strcat)
    strcat(payload, value);
    return true;
}

// This function extracts information from a requestAnswerMessage payload
bool Communications::extractRequestAnswerMessage(const char* payload, enum VariableIDs* variableID, char* value, enum FunctionIDs* functionID, byte* step)
{
    if (payload == nullptr || value == nullptr || variableID == nullptr || functionID == nullptr)
        return false;
    *variableID = (VariableIDs)payload[1];
    *functionID = (FunctionIDs)payload[2];
    *step = payload[3];
    strcpy(value, &payload[4]);
    return true;
}

// This function puts information together to create a requestMessage payload
bool Communications::createRequestMessage(char* payload, enum VariableIDs variableID, enum FunctionIDs functionID, byte step)
{
    if(payload == nullptr || step<1)
        return false;
    payload[0] = REQUESTMESSAGE_ID;
    payload[1] = variableID;
    payload[2] = functionID;
    payload[3] = step;
    payload[4] = '\0';
    return true;
}

// This function extracts information from a requestMessage payload
bool Communications::extractRequestMessage(const char* payload, enum VariableIDs* variableID, enum FunctionIDs* functionID, byte* step)
{
    if(payload == nullptr || variableID == nullptr || functionID == nullptr)
        return false;
    *variableID = (VariableIDs)payload[1];
    *functionID = (FunctionIDs)payload[2];
    *step = payload[3];
    return true;
}

// Link layer

// This function sends a message, waits for ACK & if timeout, it retries MAXMSGRETRIES of times
// On success, it returns true, otherwise false.
bool Communications::sendMessage(const char* payload, HardwareSerial* serial)
{
    byte payloadLength = strlen(payload);
    if(payloadLength>MAXPAYLOADSIZE)
    {
        debug(F("Payload exceeded maximum message size: "));debug(payloadLength);debug(F(" > "));debug(MAXPAYLOADSIZE);debug('\n');
        return false;
    }
    char message[MAXMSGSIZE];
    message[0] = 1; // This avoids strcat placing the '\n' in message[0] (this will only happen if message[0] is 0 (memory is not automatically cleared))
    message[1] = payloadLength+1; // size of [size]+[message]
    strcpy(&message[2],payload); // copy payload to message
    message[0] = CRC8((byte*)&message[1],message[1]); // set CRC of the message

    bool successfulSend = false;
    for(byte i = 0; !successfulSend && i<MAXMSGRETRIES; i++)
    {
        serial->write(message,payloadLength+3); //[CRC][size][payload]\n
        unsigned long startTime = millis();
        while (!successfulSend && millis()-startTime<MSGTIMEOUT)
        {
            successfulSend = serial->available() && serial->read()==ACK;
        }
        flush(serial);
    }
    return successfulSend;
}

// This function gets a message, verifies & extract its payload, send an ACK if the message is valid & returns if success
bool Communications::getMessage(char* payload, HardwareSerial* serial)
{
    if(serial->available())
    {
        delay(100);
        payload[0] = serial->read(); // [CRC]
        payload[1] = serial->read(); // [size]
        serial->readBytes(&payload[2], (payload[1]<MAXPAYLOADSIZE) ? payload[1] : MAXPAYLOADSIZE); // [payload]
        flush(serial);

        if (verifyMessage(payload)) // if crc match expected crc
        {
            serial->write(ACK);
            return true;
        }
        else
        {
            debug(F("A corrupted or incomplete message arrived (CRC mismatch)\nThe message was: "));
            debug(payload);
            debug('\n');
        }

    }
    return false;
}

// This function sends a message
// On success, it returns true, otherwise false.
bool Communications::sendQuickMessage(const char* payload, HardwareSerial* serial)
{
    byte payloadLength = strlen(payload);
    if(payloadLength>MAXPAYLOADSIZE)
    {
        debug(F("Payload exceeded maximum message size: "));debug(payloadLength);debug(F(" > "));debug(MAXPAYLOADSIZE);debug('\n');
        return false;
    }
    char message[MAXMSGSIZE];
    message[0] = 1; // This avoids strcat placing the '\n' in message[0] (this will only happen if message[0] is 0 (memory is not automatically cleared))
    message[1] = payloadLength+1; // size of [size]+[message]
    strcpy(&message[2],payload); // copy payload to message
    message[0] = CRC8((byte*)&message[1],message[1]); // set CRC of the message

    serial->write(message,payloadLength+3); //[CRC][size][payload]\n
    return true;
}

// This function gets a message, verifies & extract its payload & returns true if the message is valid
bool Communications::getQuickMessage(char* payload, HardwareSerial* serial)
{
    if(serial->available())
    {
        delay(100);
        payload[0] = serial->read(); // [CRC]
        payload[1] = serial->read(); // [size]
        serial->readBytes(&payload[2], (payload[1]<MAXPAYLOADSIZE) ? payload[1] : MAXPAYLOADSIZE); // [payload]

        if(verifyMessage(payload)) // if crc match expected crc
        {
            return true;
        }
        else
        {
            debug(F("A corrupted or incomplete message arrived (CRC mismatch)\nThe message was: "));
            debug(payload);
            debug('\n');
        }
    }
    return false;
}

// This function extracts the payload from a message & validates it against a precalculated CRC8
// This function modifies the given input (message) removing CRC8 code & size bytes
bool Communications::verifyMessage(char* message)
{
    byte originCRC = message[0]; // Origin CRC code
    byte size = message[1]; // size of [size]+[message]
    byte realCRC = CRC8((byte*) &message[1],size); // get CRC8 of [tam][message]
    if(originCRC==realCRC) // If message is valid
    {
        for(byte i = 0; i<size;i++)
        {
            message[i] = message [i+2]; // Delete CRC8 & size values from the payload
        }
        return true;
    }
    return false;
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
bool Communications::flush(HardwareSerial* serial)
{
    while (serial->available())
    {
        serial->read();
    }
    return true;
}

// This function awaits for the HardwareSerial object to transmit all the data pending in the internal output buffer
bool Communications::await(HardwareSerial* serial)
{
    serial->flush();
    return true;
}
