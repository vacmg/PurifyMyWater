//
// Created by Víctor on 08/03/2022.
//

#include "Communications.h"

// This function get a message from the Serial1 buffer, then it decodes and verifies it returning the message itself and its type
// If its result is false, the message couldn't be received properly
// and false is returned to proper handle the failure in the function that called getMessage
bool getMessage(char* message, char* type) // handles timeout and retry
{
    if (getMessageHelper(message, type)) // send resend last message
    {
        debug(F("getMessage - Failure receiving a message, retrying..."));
        sendMessageHelper(Message(F("R")), COMMSG);
        return true;
    }
    return false;
}

bool getMessageHelper(char* message, char* type)
{
    byte size = Serial1.readBytesUntil('\n', message, 38); // get raw message without /n or NULL
    if (size <= 0)
    {
        return false;
    }
    message[size] = '\0'; // add string NULL

    if (!verifyMessage(message))
    {
        debug(F("getMessageHelper - Message corrupted"));
        return false;
    }
    *type = message[0];

    for (byte i = 0; i < size; i++) // remove message type from the string
    {
        message[i] = message[i + 1];
    }
    debug(String(F("getMessageHelper - Got a message from type ")) + type + String(F(" and message ")) + message);
    return true;
}

// This function sends a message from the type 'type' and ensures it is received properly.
// If its result is false, the message couldn't be delivered properly
// and a false is returned to proper handle the failure in the function that called sendMessage
// TODO test timeout and retry system (needs getMessage for it to work)
bool sendMessage(const char* message, const char type)
{
    bool ok = false;

    for (byte i = 1; !ok && i <= MAXMESSAGERETRIES; i++)
    {
        if (sendMessageHelper(message, type))
        {
            unsigned long before = millis();
            while (!Serial1.available() && before + MSGTIMEOUT > millis());
            if (Serial.available())
            {
                char typ = 0;
                char msg[39] = "";
                if (getMessageHelper(msg, &typ) && typ == COMMSG && strcmp(msg, Message(F("OK"))))
                {
                    ok = true;
                }
            }
        }
        if (!ok)
        {
            debug(String(F("sendMessage - Failure sending this message: ")) + message + String(F(".\tAttempt ")) + i + String(F(" out of ")) + MAXMESSAGERETRIES);
        }

    }
    if (!ok)
    {
        debug(String(F("sendMessage - Failure sending this message: ")) + message + String(F(".\tNo more attempts left")));
    }
    return ok;
}

bool sendMessage(char* message)
{
    return(sendMessage(message, DATAMSG));
}

bool sendMessageHelper(const char* message, const char type)
{
    char sendMe[39];
    messageConstructor(type, message, sendMe); // creates message and stores in sendMe
    char temp[39];
    strcpy(temp, sendMe); // make a copy of the message and use it to verify it
    if (verifyMessage(temp))
    {
        debug(String(F("sendMessageHelper - Sending this message: '")) + sendMe + String(F("'")));
        Serial1.println(sendMe);
        return true;
    }
#if DEBUG
    else
    {
        debug(String(F("sendMessageHelper - Verification failed for message: ")) + sendMe);
    }
#endif
    return false;
}

// This function verifies the CRC8 of the message and returns true if it matches
// CAUTION: This function modifies rawMessage so after it, rawMessage only contains the message without ,C(crc8)
bool verifyMessage(char* rawMessage)
{
    if (strlen(rawMessage) > 38)
        raise(MAXMESSAGESIZEEXCEEDEDERROR, String(F("verifyMessage - The message that exceeded it is: ")) + rawMessage);
    char* message = strtok(rawMessage, ",C");
    bool res = (byte)atoi(strtok(NULL, ",C")) == CRC8((byte*)message, strlen(message));

    debug(String(F("verifyMessage - Result: ")) + res);
    return res;
}

// This function build a message appending the type and the CRC8 checksum
// The dest string MUST be of length >= 39
void messageConstructor(const char type, const char* message, char* dest)
{
    if (strlen(message) > 32) // 33 with null
        raise(MAXMESSAGESIZEEXCEEDEDERROR, String(F("messageConstructor - The message that exceeded it is: ")) + message);

    sprintf(dest, "%c", type); // size 2
    strcat(dest, message); // max size 2 - 1 + 33 = 34
    char tmp[6];
    sprintf(tmp, ",C%d", CRC8((byte*)dest, strlen(dest)));
    strcat(dest, tmp); // max size 34 - 1 + 6 = 39

    debug(String(F("messageConstructor - MessageReady is: ")) + dest);
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
void flush(HardwareSerial ser)
{
    while (ser.available())
    {
        ser.read();
    }
}
