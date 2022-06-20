//
// Created by Víctor on 08/03/2022.
//

#ifndef H2O_COMMUNICATIONS_H
#define H2O_COMMUNICATIONS_H

#define SCREENBAUDRATE 115200
#define MAXMSGRETRIES 3
#define MSGTIMEOUT 2500
#define SCREENTIMEOUT 120000
#define MAXMSGSIZE 60
#define MAXRAWMSGSIZE 64

#define ACK 6

#define ID_REQUESTMESSAGE 1
#define ID_REQUESTANSWERMESSAGE 2
#define ID_SENDMESSAGE 3
#define SEPARATOR ","

#include <Arduino.h>

/*
 * Message structure:
 * [CRC][size][payload]\n
 * CRC: CRC8 code of [size][payload]
 * size: size in bytes of [size]+[payload]
 * payload: useful data of the message
 * \n: terminator character
 */

#ifndef debug(data)
    #if DEBUG
        #define debug(data) Serial.println(data)
    #else
        #define debug(data) ;
    #endif
#endif

#ifndef Message(data)
    #define Message(data) String(data).c_str()
#endif

class Communications
{
public:
    // Application layer
    static bool createSendMessage(char* payload, byte variableID, const char* value);
    static bool extractSendMessage(const char* payload, char* variableID, char* value);
    static bool createRequestAnswerMessage(char* payload, const char* variableID, const char* value, const char* functionID);
    static bool extractRequestAnswerMessage(char* payload, char* variableID, char* value, char* functionID);
    static bool createRequestMessage(char* payload, const char* variableID, const char* functionID);
    static bool extractRequestMessage(char* payload, char* variableID, char* functionID);

// Link layer
    static bool sendMessage(const char* payload, HardwareSerial* serial);
    static bool getMessage(char* payload, HardwareSerial* serial);
    static bool verifyMessage(char* payload);
    static byte CRC8(const byte* data, size_t dataLength);
    static void flush(HardwareSerial* serial);
};

#endif //H2O_COMMUNICATIONS_H
