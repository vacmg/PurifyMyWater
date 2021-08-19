// Visual Micro

/*
    Name:       H2O_GUI.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

//todo add eeprom config

#include <Arduino.h>

/*------------Config----------------*/

#define DEBUG true

#define SCREENBAUDRATE 115200
#define SCREENALWAYSON 1 // TODO auto on/off
#define MAXMESSAGERETRIES 3
#define MAXHANDSHAKERETRIES 3
#define HANDSHAKETIMEOUT 10000
#define MSGTIMEOUT 2500
#define SCREENTIMEOUT 120000


/*------------Config----------------*/

// Define used Libraries below here or use a .h file
//


// Define User Types below here or use a .h file
//

/*------------Errors----------------*/

#define UNEXPECTEDBEHAVIORERROR 00 // The code is being executed in an unwanted way (a bug is being detected) // error code 00

#define SCREENNOTCONNECTEDERROR 30 // Cannot handsake with the screen. Probably a broken or bad connected cable or the screen didn't have the correct firmware // error code 30
#define MAXMESSAGESIZEEXCEEDEDERROR 31 // The message that is being sent exceed the max size of 32 bytes w/out header & CRC // error code 31
#define SENDMESSAGEERROR 32 // Message couldn't be sent, probably due to a bug in the sendMessage proccess

/*------------Errors----------------*/

/*------------Const&vars------------*/

    /*------------Input-----------------*/



    /*------------Input-----------------*/

    /*------------Output----------------*/


    /*------------Output----------------*/

    /*------------Other-----------------*/

#if DEBUG
    #define debug(data) sendMessage(Message(data), DEBUGMSG)
#else
    #define debug(data) ;
#endif

    /*------------Other-----------------*/

    /*---------------GUI----------------*/

#define Message(data) String(data).c_str()

#define SCREENOFF 0
#define SCREENSTARTING 1
#define SCREENON 2
#define SCREENCONNECTING 3
#define SCREENNOTCONNECTED 4
#define SCREENSHUTTINGDOWN 5

// types of messages sent from/to the screen
#define PINGMSG 'A'
#define PONGMSG 'Z'
#define DATAMSG 'D'
#define DEBUGMSG '_'
#define COMMSG '-'

byte screenStatus = SCREENOFF; // 0 = OFF, 1 = ON, 2 = Establishing connection, 3 = Unable to stablish connection
byte handshakeRetries = 0; // stores nº of handshake attempts // max nº of attempts is stored in MAXHANDSHAKERETRIES

    /*---------------GUI----------------*/

/*------------Const&vars------------*/



// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
/*------------Error Control-------------*/

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function if it is critical
// or resume the program if it is not
// This function is not completed yet
/*
void raise(byte error, String possibleExplanation)
{
    bool critical = true;
    setColor(RED);

    switch (error)
    {
#if GUI
    case SCREENNOTCONNECTEDERROR:
        critical = false;
        setColor(255, 30, 0); // orange
        break;
#endif
    default:
        currentAnimation = &defaultErrorAnimation;
        break;
    }

    if (critical)
    {
        disconnectEverything();
        delay(1000);
        voltControl();
#if DEBUG
        Serial.print(F("RAISE --- CRITICAL Error "));
        Serial.print(error);
        Serial.println(F(": "));
        Serial.println(possibleExplanation);
        delay(2000);
#endif

        long pm = millis();
        while (true)
        {
            if (pm + 1000 < millis())
            {
                voltControl();
                pm = millis();
            }
            updateAnimation();
        }
    }
    else
    {
#if DEBUG
        Serial.print(F("RAISE --- Error "));
        Serial.print(error);
        Serial.println(F(": "));
        Serial.println(possibleExplanation);
#endif
        delay(3000);
        switch (mode) // set back normal color
        {
        case TRANSITIONTOIDLE:
        case IDLE:
            setColor(UNDERVOLTAGECOLOR);
            break;
        default:
            setColor(WORKINGCOLOR);
        }
        voltControl();
    }
}
//*/void raise(byte error, String possibleExplanation) {}

/*------------Error Control-------------*/

/*-----------------GUI------------------*/



/*-----------------GUI------------------*/

/*------------COMMUNICATION-------------*/

// This function checks and answers any request from the PurifyMyWater MCU if it is conencted

void updateClient()
{
    
}

// This function checks if the screen is properly connected and available for other functions to use it
// The handshake consists of:
// The screen sends each 500ms an 'A'
// The server answers with a 'Z' once it discovers it
// The screen sends another 'Z' to end handshake
// All of this must be done in less than HANDSHAKETIMEOUT ms
bool doClientHandshake()
{
    unsigned long pm = millis();
    bool sw = 0;
    flush(Serial);
    while (!sw && pm + HANDSHAKETIMEOUT > millis())
    {
        Serial.print('A');
        delay(500);
        if (Serial.available() && Serial.read() == 'Z')
        {
            delay(200);
            Serial.print('Z');
            delay(50);
            sw = 1;
        }
    }
    flush(Serial);
    return sw;
}

//TODO processMessage(withRetryOption) 

// This function get a message from the Serial1 buffer, then it decodes and verifies it returning the message itself and its type
// If its resoult is false, the message couldn't be received properly
// and a false is returned to proper handle the failure in the function that called getMessage
bool getMessage(char* message, char* type) // handles timeout and retry
{

    if (getMessageHelper(message, type)) // send resend last message
    {
        debug(F("getMessage - Failure receiving a message, retrying..."));
        sendMessageHelper(Message(F("R")), COMMSG);
    }
}

bool getMessageHelper(char* message, char* type)
{
    byte size = Serial.readBytesUntil('\n', message, 38); // get raw message without /n or NULL
    if (size <= 0)
    {
        return false;
    }
    message[size] = '\0'; // add string NULL
    bool res = verifyMessage(message);
    if (!res)
    {
        message = NULL;
        type = NULL;
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
// If its resoult is false, the message couldn't be delivered properly
// and a false is returned to proper handle the failure in the function that called sendMessage
bool sendMessage(const char* message, const char type)
{
    bool ok = false;

    for (byte i = 1; !ok && i <= MAXMESSAGERETRIES; i++)
    {
        if (sendMessageHelper(message, type))
        {
            unsigned long before = millis();
            while (!Serial.available() && before + MSGTIMEOUT > millis());
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
#if DEBUG
        if (!ok && type != DEBUGMSG)
        {
            debug(String(F("sendMessage - Failure sending this message: ")) + message + String(F(".\tAttempt ")) + i + String(F(" out of ")) + MAXMESSAGERETRIES);
        }
#endif

    }
#if DEBUG
    if (!ok && type != DEBUGMSG)
    {
        raise(SENDMESSAGEERROR, String(F("sendMessage - Failure sending this message: ")) + message + String(F(".\tNo more attempts left")));
    }
#endif
    return ok;
}

bool sendMessage(char* message)
{
    return(sendMessage(message, DATAMSG));
}

bool sendMessageHelper(const char* message, const char type)
{
    char sendMe[39];
    messageConstructor(type, message, sendMe);
    char temp[39];
    strcpy(temp, sendMe);
    if (verifyMessage(temp))
    {
#if DEBUG
        if (type != DEBUGMSG)
            debug(String(F("sendMessageHelper - Sending this message: '")) + sendMe + String(F("'")));
#endif
        Serial.println(sendMe);
        return true;
    }
#if DEBUG
    else
    {
        if (type != DEBUGMSG)
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

#if DEBUG
    if(type != DEBUGMSG)
        debug(String(F("messageConstructor - MessageReady is: ")) + dest);
#endif
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

/*------------COMMUNICATION-------------*/

// The setup() function runs once each time the micro-controller starts
// This function does things :D TODO make description
void setup()
{
    Serial.begin(SCREENBAUDRATE);
    delay(500);
    //Serial.println(F("Setup - Booting..."));

    


    // put setup code after this line

    // TODO remove this test code
    ////////////////////
    pinMode(13, OUTPUT);
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
    delay(500);
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
    delay(500);
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
    delay(500);
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
    delay(500);

    digitalWrite(13, doClientHandshake());

    delay(60000);
    //////////////////////

//#if DEBUG
//    Serial.println(F("Setup - Ready"));
//#endif
}

#if DEBUG

// temp vars (remove after debug)
unsigned long prevmillis, perf;

#endif

// Add the main program code into the continuous loop() function
// This function does things :D TODO make description
void loop()
{
#if DEBUG
    prevmillis = millis();
#endif // DEBUG

    updateClient();

#if DEBUG
    perf = millis() - prevmillis;
#endif
}
