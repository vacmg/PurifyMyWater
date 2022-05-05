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




bool createRequestMessage(char* buffer, char* variableID, char* funcionID);
bool extractRequestMessage(char* buffer, char* variableID, char* funcionID);
bool sendMessage(const char* message, HardwareSerial* serial);
bool getMessage(char* message, HardwareSerial* serial);
bool verifyMessage(char* message);
byte CRC8(const byte* data, size_t dataLength);
void flush(HardwareSerial* serial);

#endif //H2O_COMMUNICATIONS_H
