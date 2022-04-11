//
// Created by Víctor on 08/03/2022.
//

#ifndef H2O_COMMUNICATIONS_H
#define H2O_COMMUNICATIONS_H

#define SCREENBAUDRATE 115200
#define MAXMESSAGERETRIES 3
#define MSGTIMEOUT 2500
#define SCREENTIMEOUT 120000

#include <Arduino.h>

#if DEBUG
#define debug(data) Serial.println(data)
#else
#define debug(data) ;
#endif

#define Message(data) String(data).c_str()

// types of messages sent from/to the screen
#define PINGMSG 'A'
#define PONGMSG 'Z'
#define DATAMSG 'D'
#define DEBUGMSG '_'
#define COMMSG '-'


byte CRC8(const byte* data, size_t dataLength);
void flush(HardwareSerial ser);

#endif //H2O_COMMUNICATIONS_H
