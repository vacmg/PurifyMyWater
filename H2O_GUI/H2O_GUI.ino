// Visual Micro

/*
    Name:       H2O_MASTER.ino
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
}///* */
void raise(byte error, String* possibleExplanation) {}

/*------------Error Control-------------*/

/*-----------------GUI------------------*/



/*-----------------GUI------------------*/

/*------------COMMUNICATION-------------*/

// This function checks and answers any request from the PurifyMyWater MCU if it is connected
/*
void updateClient()
{
    if(Serial.available())
    {
        char message[32];
        char type;
        if(getMessage(message,&type))
        {
            char* command = strtok(message,",");
            /*if(strcmp(message,"command") == 0)
            {
                dosomething();
            }
            else if(strcmp(message, "command2") == 0)
            {
                ...
            }*//*
        }



    }
}*/

// This function checks if the screen is properly connected and available for other functions to use it
// The handshake consists of:
// The screen sends each 500ms an 'A'
// The server answers with a 'Z' once it discovers it
// The screen sends another 'Z' to end handshake
// All of this must be done in less than HANDSHAKETIMEOUT ms
bool doClientHandshake()
{
    unsigned long pm = millis();
    bool sw = false;
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
            sw = true;
        }
    }
    flush(Serial);
    return sw;
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
