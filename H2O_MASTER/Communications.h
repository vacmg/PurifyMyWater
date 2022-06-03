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

#include <Arduino.h>

/*
 * Message structure:
 * [CRC][size][payload]\n
 * CRC: CRC8 code of [size][payload]
 * size: size in bytes of [size]+[payload]
 * payload: useful data of the message
 * \n: terminator character
 */

#if DEBUG
#define debug(data) Serial.println(data)
#else
#define debug(data) ;
#endif

#define Message(data) String(data).c_str()


// Application layer
bool createSendMessage(char* payload, byte variableID, const char* value);
bool extractSendMessage(const char* payload, char* variableID, char* value);
bool createRequestAnswerMessage(char* payload, const char* variableID, const char* value, const char* functionID);
bool extractRequestAnswerMessage(char* payload, char* variableID, char* value, char* functionID);
bool createRequestMessage(char* payload, const char* variableID, const char* functionID);
bool extractRequestMessage(char* payload, char* variableID, char* functionID);

// Link layer
bool sendMessage(const char* payload, HardwareSerial* serial);
bool getMessage(char* payload, HardwareSerial* serial);
bool verifyMessage(char* payload);
byte CRC8(const byte* data, size_t dataLength);
void flush(HardwareSerial* serial);

#endif //H2O_COMMUNICATIONS_H
