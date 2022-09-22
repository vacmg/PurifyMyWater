//
// Created by Víctor on 08/03/2022.
//

#ifndef H2O_COMMUNICATIONS_H
#define H2O_COMMUNICATIONS_H

#define MAXMSGRETRIES 3
#define MSGTIMEOUT 2500
#define MAXPAYLOADSIZE 61

#define MAXMSGSIZE MAXPAYLOADSIZE + 3 // payload+1(size)+1(crc)+1(NULL) // Arduino Serial buffers have 64 bytes by default, to use more space (up to 256B), use #define SERIAL_TX_BUFFER_SIZE xx & SERIAL_RX_BUFFER_SIZE
#define MAXVALUESIZE MAXPAYLOADSIZE - 5 // payloadsize - 1(MessageType)-1(variableID)-1(functionID)-1(step)-1(NULL)
#define MAXBLOBSIZE MAXVALUESIZE - 3

#define ACK 6

#define REQUESTMESSAGE_ID 1
#define REQUESTANSWERMESSAGE_ID 2
#define SENDMESSAGE_ID 3
#define BLOBMESSAGE_ID 4

#include <Arduino.h>
#include "../SharedData.h"

/*
 * [CRC][size][payload]
 * CRC: CRC8 code of [size][payload]
 * size: size in bytes of [size]+[payload]
 * payload: useful data of the message
 */

class Communications
{
public:
    static byte* blobPtr;

    // Application layer

    // This function puts information together to create a sendMessage payload
    static bool createSendMessage(char* payload, enum VariableIDs variableID, const char* value);
    static bool createSendMessage(char* payload, enum VariableIDs variableID, const char* value, byte valueSize);

    // This function extracts information from a sendMessage payload
    static bool extractSendMessage(const char* payload, enum VariableIDs* variableID, char* value);
    static bool extractSendMessage(const char* payload, enum VariableIDs* variableID, char* value, byte valueSize);

    // This function puts information together to create a requestAnswerMessage payload
    static bool createRequestAnswerMessage(char* payload, enum VariableIDs variableID, const char* value, enum FunctionIDs functionID, byte step);
    static bool createRequestAnswerMessage(char* payload, enum VariableIDs variableID, const char* value, enum FunctionIDs functionID, byte step, byte valueSize);

    // This function extracts information from a requestAnswerMessage payload
    static bool extractRequestAnswerMessage(const char* payload, enum VariableIDs* variableID, char* value, enum FunctionIDs* functionID, byte* step);
    static bool extractRequestAnswerMessage(const char* payload, enum VariableIDs* variableID, char* value, enum FunctionIDs* functionID, byte* step, byte valueSize);

    // This function puts information together to create a requestMessage payload
    static bool createRequestMessage(char* payload, enum VariableIDs variableID, enum FunctionIDs functionID, byte step);

    // This function extracts information from a requestMessage payload
    static bool extractRequestMessage(const char* payload, enum VariableIDs* variableID, enum FunctionIDs* functionID, byte* step);

    //this function puts information from a BlobMessage payload
    static bool createSendBlobMessage(byte *payload, enum VariableIDs variableID, char blobSize, unsigned char *blob);

    //this function extracts information from a BlobMessage payload
    static bool extractSendBlobMessage(char *payload, enum VariableIDs *variableID, char *blobSize, unsigned char *blob);

    static bool sendBlobMessage(char *payload, enum VariableIDs variableID, byte size, byte* value, HardwareSerial* serial);

    static bool extractSendBlobMessage(char *value, enum VariableIDs *variableID, byte *blobSize, byte *currentByte);
    static bool extractBlobMessage(char *value, enum VariableIDs *variableID);

    // Link layer

    // This function sends a message, waits for ACK & if timeout, it retries MAXMSGRETRIES of times
    // On success, it returns true, otherwise false.
    static bool sendMessage(const char* payload, byte length, HardwareSerial* serial);
    static bool sendMessage(const char* payload, HardwareSerial* serial);

    // This function gets a message, verifies & extract its payload (of size MAXMSGSIZE), send an ACK if the message is valid & returns true if success
    static bool getMessage(char* payload, HardwareSerial* serial);

    // This function sends a message
    // On success, it returns true, otherwise false.
    static bool sendQuickMessage(const char* payload, HardwareSerial* serial);

    // This function gets a message, verifies & extract its payload (of size MAXMSGSIZE) & returns true if the message is valid
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
