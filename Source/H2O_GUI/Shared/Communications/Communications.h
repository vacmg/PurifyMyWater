//
// Created by Víctor on 08/03/2022.
//

#ifndef H2O_COMMUNICATIONS_H
#define H2O_COMMUNICATIONS_H

#define MAXMSGRETRIES 3
#define MSGTIMEOUT 2500
#define MAXPAYLOADSIZE 60

#define MAXMSGSIZE MAXPAYLOADSIZE + 4 // payload+1(size)+1(crc)+1(\n terminator)+1(NULL) // Arduino Serial buffers have 64 bytes by default, to use more space (up to 256B), use #define SERIAL_TX_BUFFER_SIZE xx & SERIAL_RX_BUFFER_SIZE
#define MAXVALUESIZE MAXPAYLOADSIZE - 5 // payloadsize - 1(MessageType)-1(variableID)-1(functionID)-1(step)-1(NULL)
#define SEPARATOR ","

#define ACK 6

#define REQUESTMESSAGE_ID 1
#define REQUESTANSWERMESSAGE_ID 2
#define SENDMESSAGE_ID 3

#include <Arduino.h>
#include "../SharedData.h"

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
        #define debug(data) Serial.print(data)
    #else
        #define debug(data) ;
    #endif
#endif

class Communications
{
public:
    // Application layer

    // This function puts information together to create a sendMessage payload
    static bool createSendMessage(char* payload, enum VariableIDs variableID, const char* value);

    // This function extracts information from a sendMessage payload
    static bool extractSendMessage(const char* payload, enum VariableIDs* variableID, char* value);

    // This function puts information together to create a requestAnswerMessage payload
    static bool createRequestAnswerMessage(char* payload, enum VariableIDs variableID, const char* value, enum FunctionIDs functionID, byte step);

    // This function extracts information from a requestAnswerMessage payload
    static bool extractRequestAnswerMessage(const char* payload, enum VariableIDs* variableID, char* value, enum FunctionIDs* functionID, byte* step);

    // This function puts information together to create a requestMessage payload
    static bool createRequestMessage(char* payload, enum VariableIDs variableID, enum FunctionIDs functionID, byte step);

    // This function extracts information from a requestMessage payload
    static bool extractRequestMessage(const char* payload, enum VariableIDs* variableID, enum FunctionIDs* functionID, byte* step);

    // Link layer

    // This function sends a message, waits for ACK & if timeout, it retries MAXMSGRETRIES of times
    // On success, it returns true, otherwise false.
    static bool sendMessage(const char* payload, HardwareSerial* serial);

    // This function gets a message, verifies & extract its payload, send an ACK if the message is valid & returns true if success
    static bool getMessage(char* payload, HardwareSerial* serial);

    // This function sends a message
    // On success, it returns true, otherwise false.
    static bool sendQuickMessage(const char* payload, HardwareSerial* serial);

    // This function gets a message, verifies & extract its payload & returns true if the message is valid
    static bool getQuickMessage(char* payload, HardwareSerial* serial);

    // This function flushes an input HardwareSerial and discards all data on the input buffer
    static bool flush(HardwareSerial* serial);

    // This function awaits for the HardwareSerial object to transmit all the data pending in the internal output buffer
    static bool await(HardwareSerial* serial);

private:
    // This function extracts the payload from a message & validates it against a precalculated CRC8
    // This function modifies the given input (message) removing CRC8 code & size bytes
    static bool verifyMessage(char* payload);

    //This function returns a CRC8 Checksum code from an array of any size
    static byte CRC8(const byte* data, size_t dataLength);
};

#include "Communications.cpp"

#endif //H2O_COMMUNICATIONS_H
