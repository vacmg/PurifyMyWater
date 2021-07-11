// Visual Micro
// 
/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

//todo add eeprom config

#include <Arduino.h>

/*------------Config----------------*/

#define DEBUG true
#define GUI true
#define ONLYVITALACTIVITYALLOWED true
#define TEMPERATURE true
#define OVERRRIDEMAXVOLTAGE false // useful to check some functions without powering all the system

#define STARTCHARGINGVOLTAGE 13
#define STOPCHARGINGVOLTAGE 15.75
#define STARTWORKINGVOLTAGE 15
#define STOPWORKINGVOLTAGE 12

#define DCAmpSensivity 0.1135 //sensor sensivity in Volts/Amps // 5.4A for 60w test load
#define DCAmpZero 2.4956 // sensor voltage for 0 Amps current

#define ACAmpZero -0.07157 // sensor calibration correction value
#define ACAmpSensivity 0.033 // sensor sensivity in Volts/Amps // 0.25A for 60w test load
#define ACFrequency 50 // AC signal frequency (Hz)

#define UVPUMPFLOW 55 // 171 // UV pump flow in L/H
#define ESTIMATEDUVAMPERAGE -1.0 // Minimum estimated current that the UV light uses // todo place real value

// If any of this pumps work for more than the specified milliseconds, raise PUMPTIMEOUTERROR
#define WELLPUMPTIMEOUT 60000
#define UVPUMPTIMEOUT 60000
#define ENDPUMPTIMEOUT 60000
#define FILTERTIMEOUT 60000

#if TEMPERATURE
    #define TEMPCHECKTIME 10000
    #define STOPWORKINGTEMP 65
    #define MAXCASETEMP 40
    #define MINCASETEMP 38
    #define MAXPSUTEMP 40
    #define MINPSUTEMP 38
#endif

#if GUI
    #define SCREENBAUDRATE 115200
    #define SCREENALWAYSON 1 // TODO auto on/off
    #define MAXRETRIES 3
    #define HANDSHAKETIMEOUT 2500
    #define SENDMSGTIMEOUT 2500
    #define SCREENTIMEOUT 120000
#endif

/*------------Config----------------*/

// Define used Libraries below here or use a .h file
//

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Filters.h>

// Define User Types below here or use a .h file
//

/*------------Errors----------------*/

#define UNEXPECTEDBEHAVIORERROR 00 // The code is being executed in an unwanted way (a bug is being detected) // error code 00

#if TEMPERATURE
    #define TEMPSENSORSAMOUNTERROR 10 // Some temp sensors are not properly connected to the onewire bus // error code 10
    #define EXTREMEHOTTEMPERROR 11 // Control system temperatures are extremely high and it is dangerous to operate // error code 11
#endif

#define BUOYINCONGRUENCEERROR 20 // The system has detected an incongruence with the readings of the buoy sensors (often caused by a non connected or malfunctioning buoy) // error code 21
#define PUMPTIMEOUTERROR 21 // The system has spent so much time with a pump working. Probably the circuit has a leak or a pump is not working properly // error code 22
#define UVLIGHTNOTWORKINGERROR 22 // The UV amperage sensor didn't detect enough current. The UV light must be either broken or disconnected (check and replace the UV light) // error code 23

#if GUI
    #define SCREENNOTCONNECTEDERROR 30 // Cannot handsake with the screen. Probably a broken or bad connected cable or the screen didn't have the correct firmware // error code 30
    #define MAXMESSAGESIZEEXCEEDEDERROR 31 // The message that is being sent exceed the max size of 32 bytes w/out header & CRC // error code 31
#endif 

/*------------Errors----------------*/

/*------------Const&vars------------*/

    /*------------Input-----------------*/

const byte voltSensor = A0;
const byte mainAmpSensor = A1;
const byte UVAmpSensor = A2;

const byte secBuoy = 2;
const byte lowSurfaceBuoy = 3;
const byte highSurfaceBuoy = 4;
const byte lowFilteredBuoy = 5;
const byte highFilteredBuoy = 6;
const byte lowPurifiedBuoy = 7;
const byte highPurifiedBuoy = 8;
const byte endBuoy = 9;
const byte tempPin = 48;
#if GUI
    const byte screenSensor = 23; // 1 = case open, 2 = case closed
#endif

RunningStatistics inputStats;                 // create statistics to look at the raw test signal
bool ACAmpsDoMeasurement = false; // boolean value used as a switch to begin measuring AC current

    /*------------Input-----------------*/

    /*------------Output----------------*/

#define BLACK 0, 0, 0
#define RED 255, 0 ,0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define WHITE 255, 255, 255
#define YELLOW 255, 255, 0
#define CYAN 0, 255, 255
#define PURPLE 255, 0, 255

// Tie an action to a specific color
#define UNDERVOLTAGECOLOR PURPLE 
#define WORKINGCOLOR CYAN   
#define BOOTINGCOLOR YELLOW

const byte voltSSRelay = 33;
const byte voltRelay = 49;
const byte ACInverter = 45;
const byte wellPump = 43;
const byte UVPump = 39;
const byte endPump = 41;
const byte UVRelay = 37;
const byte filterRelay = 35;
const byte outFan = 22;
const byte PSUFan = 24;
const byte inFan = 26;
const byte redLed = 10;
const byte greenLed = 12;
const byte blueLed = 11;
#if GUI
const byte screenRelay = 47;
#endif

bool pumpSt[4] = { false, false, false, false }; // Used to store the status of each pump and also the filter where true is on and false is off // { well, UV, end, filter }
unsigned long pumpPrevMillis[4] = { 0,0,0,0 }; // Used to check for PUMPTIMEOUTERROR // pumpPrevMillis[1] also stores UV working start time // { well, UV, end, filter }

typedef struct ledAnimation
{
    int frameDelay; // Delay between frames (in ms)
    byte animationSize; // Number of used frames
    byte currentFrame; // Current frame
    byte animation[16][3]; // Up to 16 frames per animation
};

ledAnimation* currentAnimation; // Pointer to current animation
unsigned long prevAnimationMillis = 0;

ledAnimation testAnimation = { 1500,5,0,{{255,0,0},{0,255,0},{0,0,255},{255,255,255},{0,0,0}} };
ledAnimation defaultErrorAnimation = { 500,2,0,{{255,0,0},{0,0,0}} };

    /*------------Output----------------*/

    /*------------Temperature-----------*/

unsigned long tempMillis = 0;

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(tempPin);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

#define INSENSOR 2
#define OUTSENSOR 0
#define PSUSENSOR 1

    /*------------Temperature-----------*/

    /*------------Other-----------------*/

#define TRANSITIONTOIDLE 0
#define IDLE 1
#define TRANSITIONTOPUMPSWORKING 2
#define PUMPSWORKING 3
#define TRANSITIONTOFILTERWORKING 4
#define FILTERWORKING 5

byte mode = TRANSITIONTOIDLE; // Working mode is changed using this variable
unsigned long UVMillis = 0;
unsigned long workingTime = 0; // Time that UV pump is working (in ms) // Used to calculate the amount of purified water
double purifiedWater = 0.00; // Amount of water purified since the start of the machine (in L)

    /*------------Other-----------------*/

    /*---------------GUI----------------*/
#if GUI
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
    #define PROCCESSINGMSG '-'

    byte screenStatus = SCREENOFF; // 0 = OFF, 1 = ON, 2 = Establishing connection, 3 = Unable to stablish connection
    byte handshakeRetries = 0; // stores n� of handshake attempts // max n� of attempts before raising SCREENNOTCONNECTEDERROR = 3
#endif
    /*---------------GUI----------------*/

/*------------Const&vars------------*/



// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

/*------------Temp Control--------------*/
#if TEMPERATURE

// Used to get temperature in celsius of the 3 temperature sensors
// It modifies the given array that MUST be of length 3
void getSensorsTemp(float* temp)
{
    sensors.requestTemperatures();
    for (int i = 0; i < 3; i++)
    {
        temp[i] = sensors.getTempCByIndex(i);
    }
}

// Used to control the temperature of the main control unit
void tempControl()
{
    float temp[3];
    getSensorsTemp(temp);

    // Start or stop fans according to external and internal temperature
    if (temp[INSENSOR] > MAXCASETEMP && temp[OUTSENSOR] < temp[INSENSOR])
    {
        output(inFan, 1);
        output(outFan, 1);
    }
    else if (temp[INSENSOR] < MINCASETEMP || temp[OUTSENSOR] >= temp[INSENSOR])
    {
        output(inFan, 0);
        output(outFan, 0);
    }

    if (temp[PSUSENSOR] > MAXPSUTEMP && temp[INSENSOR] < temp[PSUSENSOR])
    {
        output(PSUFan, 1);
    }
    else if (temp[PSUSENSOR] < MINPSUTEMP || temp[INSENSOR] >= temp[PSUSENSOR])
    {
        output(PSUFan, 0);
    }

    // check for extreme temperatures
    bool ok = true;
    for (byte i = 0; i < 3 && ok; i++)
    {
        if (temp[i] > STOPWORKINGTEMP)
        {
            ok = false;
        }
    }
    if (!ok)
    {
        raise(EXTREMEHOTTEMPERROR, String(F("Current temps are: ")) + String(temp[0]) + String(F(", ")) + String(temp[1]) + String(F(", ")) + String(temp[2]));
    }
}
#endif
/*------------Temp Control--------------*/

/*------------Output Control------------*/

// Depending on the hardware used, relays are activated with high or low signals.
// To maintain readability, in this function we set what kind of signal we need to activate those relays
// A true value means that the circuit is closed whereas a false means that the circuit is opened
void output(byte pin, bool value)
{
    if (!(pin == redLed || pin == greenLed || pin == blueLed || pin == voltRelay || pin == outFan || pin == PSUFan || pin == inFan))
    {
        value = !value;
    }
    digitalWrite(pin, value);
}

// Used to set a color on the rgb status led by setting the amount of each color from 0 to 255
void setColor(byte color[3])
{
    analogWrite(redLed, color[0]);
    analogWrite(greenLed, color[1]);
    analogWrite(blueLed, color[2]);
}

// Used to set a color on the rgb status led by setting the amount of each color from 0 to 255
void setColor(byte r, byte g, byte b)
{
    analogWrite(redLed, r);
    analogWrite(greenLed, g);
    analogWrite(blueLed, b);
}

// This function is used to perform animations on the RGB status led.
// If an animation is loaded in currentAnimation and this function is called everytime, the animation will be displayed on the led
void updateAnimation()
{
    if (currentAnimation != NULL && millis() > prevAnimationMillis + currentAnimation->frameDelay)
    {
        setColor(currentAnimation->animation[currentAnimation->currentFrame]);
        if (currentAnimation->currentFrame + 1 >= currentAnimation->animationSize)
        {
            currentAnimation->currentFrame = 0;
        }
        else
        {
            currentAnimation->currentFrame++;
        }
        prevAnimationMillis = millis();
    }
}

/*------------Output Control------------*/

/*------------Voltage Control-----------*/

// used to scale any float value (Thales theorem)
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// This function reads from a 0-25V DC sensor and returns its voltage
float voltRead()
{
    float f = fmap(analogRead(voltSensor), 0, 1023, 0.0, 25.0);   // read from sensor and ajust the scale to 0-25V
    return f - loadOffset();
}

// This function generates an offset to correctly measure real voltage under heavy loads
float loadOffset()
{
    float load = getDCAmps(200); // get current load
    //float formula = load * -0.65; // one big pump // 1.5A
    //float formula = load * -0.375; // two big pumps // 3A
    //float formula = load * -0.50; // 1 pump + UV // 2.5A
    //float formula = load * -0.80; // UV // 1A
    //float formula = load * -0.3; // 2 big pumps + UV // 4A
    //float formula = load * -0.20; // Filter // 5.4A
    //float formula = load * 0.00 - 1.00; // no load // 0A

    // Using some known pairs of current and difference from real to arduino measured voltage, here we used least square roots to approximate to the ecuation of a straight line
    float formula = -0.9487 - 0.0453 * load; // f(I)=-0.9487-0.0453*I
    //Serial.println(load);
    return formula;
}

// This function maintains the voltage in the supercapacitors between STARTCHARGINGVOLTAGE and STOPCHARGINGVOLTAGE
// It MUST be called at least one time each 2 seconds
void voltControl()
{
    float voltage = voltRead();
    Serial.println(voltage);
    if (voltage < STARTCHARGINGVOLTAGE)
    {
        output(voltSSRelay, 1);
    }
    else if (voltage > STOPCHARGINGVOLTAGE)
    {
        output(voltSSRelay, 0);
    }
}

// This functions blocks the code execution until a certain voltage is reached inside the supercapacitors
void waitForVoltage(float volts)
{
    float voltage = voltRead();
#if OVERRRIDEMAXVOLTAGE
    voltage = volts + 1;
#endif
    if (voltage < volts)
    {
        output(voltSSRelay, 1);
        while (voltage < volts)
        {
            voltage = voltRead();
        }
        output(voltSSRelay, 0);
    }
}

/*------------Voltage Control-----------*/

/*------------Amperage Control----------*/

// This function returns the amperage of the main sensor
float getDCAmps(int samples)
{
    float sensorVolts;
    float corriente = 0;
    for (int i = 0; i < samples; i++)
    {
        sensorVolts = analogRead(mainAmpSensor) * (5.0 / 1023.0); // sensor reading
        corriente = corriente + (sensorVolts - DCAmpZero) / DCAmpSensivity; // Proccess input to get Amperage
    }
    corriente = corriente / samples;
    return(corriente >=0 ? corriente : 0);
}

// This function uses all the data logged by logACAmps() and calculates an RMS Amperage value for the UV sensor
float getACAmps()
{
    float amps = ACAmpZero + ACAmpSensivity * inputStats.sigma();
    return(amps >= 0 ? amps : 0); // calculate RMS Amperage
}

// To measure AC current, arduino must log sensor data all the time. This function read and log one value per call
void logACAmps()
{
    inputStats.input(analogRead(UVAmpSensor));  // log to Stats function
}

/*------------Amperage Control----------*/

/*------------Error Control-------------*/

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function if it is critical
// or resume the program if it is not
// This function is not completed yet
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
            Serial.print(F("RAISE --- Error "));
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

// This function will check for hardware errors on the system
void errorCheck()
{
    // Check for buoy incongruences
    if (!digitalRead(lowSurfaceBuoy) && digitalRead(highSurfaceBuoy))
    {
        raise(BUOYINCONGRUENCEERROR, F("An incongruence has been detected with either lowSurfaceBuoy or highSurfaceBuoy. Please check the connections to those sensors"));
    }
    if (!digitalRead(lowFilteredBuoy) && digitalRead(highFilteredBuoy))
    {
        raise(BUOYINCONGRUENCEERROR, F("An incongruence has been detected with either lowFilteredBuoy or highFilteredBuoy. Please check the connections to those sensors"));
    }
    if (!digitalRead(lowPurifiedBuoy) && digitalRead(highPurifiedBuoy))
    {
        raise(BUOYINCONGRUENCEERROR, F("An incongruence has been detected with either lowPurifiedBuoy or highPurifiedBuoy. Please check the connections to those sensors"));
    }
    
    // Check for pumps timeout
    if (pumpSt[0] && millis() > pumpPrevMillis[0] + WELLPUMPTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("Well pump has been working for more than ")) + String(WELLPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the well pump's circuit")));
    }
    if (pumpSt[1] && millis() > pumpPrevMillis[1] + UVPUMPTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("UV pump has been working for more than ")) + String(UVPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in UV the pump's circuit")));
    }
    if (pumpSt[2] && millis() > pumpPrevMillis[2] + ENDPUMPTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("Well pump has been working for more than ")) + String(ENDPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the end pump's circuit")));
    }
    if (pumpSt[3] && millis() > pumpPrevMillis[3] + FILTERTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("Filter has been working for more than ")) + String(FILTERTIMEOUT) + String(F("ms. Either the filter doesn't work or there is a leakage in the filter's circuit")));
    }
}

// Quick shortcut to disconnect every pump or relay
void disconnectEverything()
{
    output(voltSSRelay, 0);
    output(voltRelay, 0);
    output(ACInverter, 0);
    output(wellPump, 0);
    output(UVPump, 0);
    output(endPump, 0);
    output(UVRelay, 0);
    output(filterRelay, 0);
    #if DEBUG
        Serial.println(F("DisconenctEverything - Done"));
    #endif
}

/*------------Error Control-------------*/

/*-----------------GUI------------------*/

#if GUI

// This function checks and answers any request from the screen client if it is conencted
void updateServer()
{
    switch (screenStatus)
    {
    case SCREENSHUTTINGDOWN:
        Serial1.end();
        screenStatus = SCREENOFF;
        break;
    case SCREENSTARTING:
        Serial1.begin(SCREENBAUDRATE);
        screenStatus = SCREENCONNECTING;
        break;
    case SCREENCONNECTING:
        if (doHandshake())
        {
            screenStatus = SCREENON;
        }
        else if (++handshakeRetries >= 3) // TODO test this
        {
            screenStatus = SCREENNOTCONNECTED;
            raise(SCREENNOTCONNECTEDERROR, F("Unable to communicate to the screen, double check the connections to it"));
        }

        break;
    case SCREENON:
        if (Serial1.available())
        {
            // TODO Server side stuff
        }
        break;
    }
}

// The handshake consists of:
// The screen sends each 500ms an 'A'
// The server answers with a 'Z' once it discovers it
// The screen sends another 'Z' to end handshake
// All of this must be done in less than HANDSHAKETIMEOUT ms

// TODO handshake with CRC8
bool doHandshake()
{
    unsigned long pm = millis();
    bool sw = 0;
    while (pm + HANDSHAKETIMEOUT < millis())
    {
        if (!sw && Serial1.available() && Serial1.read() == 'A')
        {
            delay(50);
            Serial1.print('Z');
            delay(50);
            sw = 1;
        }
        else if (sw && Serial1.available() && Serial1.read() == 'Z')
        {
            return true;
        }
    }
    return false;
}

//TODO getMessage, verifyMessage, CRC8, processMessage(withRetryOption), sendMessage(withRetryOption), messageConstructor

bool getMessage(char* message, char* type) // handles timeout and retry
{

}

bool getMessageHelper(char* message, char* type) // gets message form buffer, decodes and verifies it
{
    byte size = Serial1.readBytesUntil('\n', message, 38); // get raw message without /n or NULL
    message[size] = '\0'; // add string NULL
    bool res = verifyMessage(message);
    if (!res)
    {
        message = NULL;
        type = NULL;
        #if DEBUG
            Serial.println(F("getMessageHelper - Message corrupted"));
        #endif
        return false;
    }
    *type = message[0];

    for (byte i = 0; i < size; i++) // remove message type from the string
    {
        message[i] = message[i + 1];
    }
    #if DEBUG
        Serial.println(String(F("getMessageHelper - Got a message from type "))+type+String(F(" and message "))+message);
    #endif
    return true;
}

// This function sends a message from the type type and ensures it is received properly.
// If its resoult is false, the message couldn't be delivered properly
// TODO timeout and retry system (needs getMessage for it to work)
bool sendMessage(char type, char* message)
{
    bool ok = false;
    for (byte i = 1; !ok && i <= MAXRETRIES; i++)
    {
        char sendMe[39];
        messageConstructor(type, message, sendMe);
        char temp[39];
        strcpy(temp, sendMe);
        if (verifyMessage(temp))
        {
            Serial1.println(sendMe);
            #if DEBUG
                Serial.println(String(F("sendMessage - Sending this message: ")) + sendMe);
            #endif
            
            ok = true;
            /*unsigned long pm = millis();
            while (!Serial1.available() && pm + SENDMSGTIMEOUT > millis()); // wait for message or timeout
            if (Serial1.available())
            todotimeoutandretry*/
        }
        #if DEBUG
            else
            {
                Serial.print(F("Verification failed for message: "));
                Serial.println(sendMe);
                Serial.print(F("Retrying for "));
                Serial.print(i);
                Serial.println(F(" time"));
            }
        #endif
    }
    return ok;
}

// This function verifies the CRC8 of the message and returns true if it matches
// CAUTION: This function modifies rawMessage so after it, rawMessage only contains the message without ,C(crc8)
bool verifyMessage(char* rawMessage)
{
    if (strlen(rawMessage) > 38)
        raise(MAXMESSAGESIZEEXCEEDEDERROR, String(F("verifyMessage - The message that exceeded it is: ")) + rawMessage);
    char* message = strtok(rawMessage, ",C");
    bool res = (byte)atoi(strtok(NULL, ",C")) == CRC8((byte*)message, strlen(message));

#if DEBUG
    Serial.println(String(F("verifyMessage - Result: "))+res);
#endif

    return res;
}

// This function build a message appending the type and the CRC8 checksum
// The dest string MUST be of length >= 39
void messageConstructor(char type, char* message, char* dest)
{
    if (strlen(message) > 32) // 33 with null
        raise(MAXMESSAGESIZEEXCEEDEDERROR, String(F("messageConstructor - The message that exceeded it is: ")) + message);

    sprintf(dest, "%c", type); // size 2
    strcat(dest, message); // max size 2 - 1 + 33 = 34
    char tmp[6];
    sprintf(tmp, ",C%d", CRC8((byte*)dest, strlen(dest)));
    strcat(dest, tmp); // max size 34 - 1 + 6 = 39

#if DEBUG
    Serial.println(String(F("messageConstructor - MessageReady is: ")) + dest);
#endif
}

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

#endif

/*-----------------GUI------------------*/

// The setup() function runs once each time the micro-controller starts
// This function starts serial communication if defined, configures every input and output, set any other variable that needs to and waits for enough voltage in the capacitors to start operating
void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(500);
    Serial.println(F("Setup - Booting..."));
#endif
  
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    setColor(BOOTINGCOLOR);

#if TEMPERATURE
    sensors.begin();
    if (sensors.getDeviceCount() < 3)
    {
        raise(TEMPSENSORSAMOUNTERROR, String(F("Setup - Less than 3 sensors were connected.\nNumber of sensors detected: "))+String(sensors.getDeviceCount()));
    }
#endif

    pinMode(secBuoy, INPUT);
    pinMode(lowSurfaceBuoy, INPUT);
    pinMode(highSurfaceBuoy, INPUT);
    pinMode(lowFilteredBuoy, INPUT);
    pinMode(highFilteredBuoy, INPUT);
    pinMode(lowPurifiedBuoy, INPUT);
    pinMode(highPurifiedBuoy, INPUT);
    pinMode(endBuoy, INPUT);

    pinMode(voltSSRelay, OUTPUT);
    pinMode(voltRelay, OUTPUT);
    pinMode(ACInverter, OUTPUT);
    pinMode(wellPump, OUTPUT);
    pinMode(UVPump, OUTPUT);
    pinMode(endPump, OUTPUT);
    pinMode(UVRelay, OUTPUT);
    pinMode(filterRelay, OUTPUT);

    output(voltSSRelay, 0);
    output(voltRelay, 1);
    output(ACInverter, 0);
    output(wellPump, 0);
    output(UVPump, 0);
    output(endPump, 0);
    output(UVRelay, 0);
    output(filterRelay, 0);

#if TEMPERATURE
    pinMode(outFan, OUTPUT);
    pinMode(PSUFan, OUTPUT);
    pinMode(inFan, OUTPUT);
    output(outFan, 1);
    output(PSUFan, 1);
    output(inFan, 1);
#endif

#if GUI
    pinMode(screenSensor, INPUT_PULLUP);
    pinMode(screenRelay, OUTPUT);
    #if SCREENALWAYSON
        output(screenRelay, 1);
    #else
        output(screenRelay, 0);
    #endif

    /**/
    Serial1.begin(115200); // TODO remove all these lines
    delay(1000);
    while (Serial1.available())
    {
        Serial1.read();
    }
    Serial1.println("Hello world"); 
    delay(1000);
    /**/
#endif
#if ONLYVITALACTIVITYALLOWED
    currentAnimation = &testAnimation;
#else
    #if TEMPERATURE
        tempControl();
    #endif
    #if DEBUG
        Serial.print(F("Setup - Waiting for "));
        Serial.print(STARTCHARGINGVOLTAGE - 1);
        Serial.println(F(" V"));
    #endif
    waitForVoltage(STARTCHARGINGVOLTAGE - 1);
#endif
    output(voltRelay, 0);

    // put setup code after this line



    char msg[39];
    char type;
    //sendMessage(DEBUGMSG, "Waiting for message...");
    //messageConstructor(DATAMSG, "Alo polisia", msg);
    while (!Serial1.available());
    Serial.println(getMessageHelper(msg, &type)); // A,C24
    Serial.println(type);
    Serial.println(msg);
    Serial.println("Done");
    
    delay(60000);



    inputStats.setWindowSecs(40.0 / ACFrequency);     //Set AC Amperemeter frequency

    mode = 0;
#if DEBUG
    Serial.println(F("Setup - Ready"));
#endif
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
        readAllSensors(); // temporal debug function
    #endif // DEBUG

    voltControl();
    logACAmps();

    #if !ONLYVITALACTIVITYALLOWED
        errorCheck();
    #endif
    
    updateAnimation();

    #if TEMPERATURE
        if (millis() > tempMillis + TEMPCHECKTIME)
        {
            tempControl();
            tempMillis = millis();
        }
    #endif

    #if !ONLYVITALACTIVITYALLOWED
        switch (mode)
        {
        case TRANSITIONTOIDLE: // Transition to OFF
            output(wellPump, 0);
            output(endPump, 0);
            output(UVPump, 0);
            output(filterRelay, 0);
            output(ACInverter, 0);
            delay(1000);
            output(UVRelay, 0);
            output(voltSSRelay, 1);
            setColor(UNDERVOLTAGECOLOR);
            for (byte i = 0; i < 3; i++)
            {
                pumpSt[i] = false;
            }
            mode = IDLE;
            break;
        case IDLE: // OFF
        #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() > STARTWORKINGVOLTAGE)
        #endif
                mode = TRANSITIONTOPUMPSWORKING;
            break;
        case TRANSITIONTOPUMPSWORKING: // Transition to Pumps Working
            output(ACInverter, 0);
            setColor(WORKINGCOLOR);
            for (byte i = 0; i < 3; i++)
            {
                pumpSt[i] = false;
            }
            mode = PUMPSWORKING;
            break;
        case PUMPSWORKING: // Pumps Working
            #if !OVERRRIDEMAXVOLTAGE
                if (voltRead() < STOPWORKINGVOLTAGE)
                    mode = TRANSITIONTOIDLE;
            #endif

            if (!pumpSt[0] && !digitalRead(highSurfaceBuoy) && digitalRead(secBuoy))
            {
                output(wellPump, 1);
                pumpPrevMillis[0] = millis();
                pumpSt[0] = true;
            }
            

            if (pumpSt[0] && (digitalRead(highSurfaceBuoy) || !digitalRead(secBuoy)))
            {
                output(wellPump, 0);
                pumpSt[0] = false;
            }
            

            if (!digitalRead(lowFilteredBuoy) && digitalRead(highSurfaceBuoy))
                mode = TRANSITIONTOFILTERWORKING;

            if (!pumpSt[1] && !digitalRead(highPurifiedBuoy) && digitalRead(lowFilteredBuoy))
            {
                output(ACInverter, 1);
                delay(250);
                output(UVRelay, 1);

                // check if UV is working
                for (int i = 0; i < 100; i++)
                {
                    logACAmps();
                    delay(10);
                }
                float amps = getACAmps();

                if (amps < ESTIMATEDUVAMPERAGE)
                {
                    raise(UVLIGHTNOTWORKINGERROR, String(F("The UV amperage sensor detected "))+String(amps)+String(F("A. The UV light must be either broken or disconnected. Check the connections and if it persists, replace the UV light")));
                }

                pumpPrevMillis[1] = millis();
                UVMillis = pumpPrevMillis[1];
                output(UVPump, 1);
                pumpSt[1] = true;
            }
            if (pumpSt[1]) // if UV is on and each 800ms
            {
                workingTime += millis() - UVMillis; // Add this time to workingTime
                purifiedWater = (workingTime * UVPUMPFLOW) / 3600000.00; // calculate the amount of purified water
                UVMillis = millis();
            }

            if (pumpSt[1] && (!digitalRead(lowFilteredBuoy) || digitalRead(highPurifiedBuoy)))
            {
                output(UVPump, 0);
                workingTime += millis() - UVMillis; // Add this time to workingTime
                purifiedWater = (workingTime * UVPUMPFLOW) / 3600000.00; // calculate the amount of purified water
                delay(1000);
                output(UVRelay, 0);
                delay(250);
                output(ACInverter, 0);
                pumpSt[1] = false;
            }

            if (!pumpSt[2] && !digitalRead(endBuoy) && digitalRead(lowPurifiedBuoy))
            {
                output(endPump, 1);
                pumpPrevMillis[2] = millis();
                pumpSt[2] = true;
            }

            if (pumpSt[2] && (!digitalRead(lowPurifiedBuoy) || digitalRead(endBuoy)))
            {
                output(endPump, 0);
                pumpSt[2] = false;
            }

            break;
        case TRANSITIONTOFILTERWORKING: // Transition to filter working
            output(wellPump, 0);
            output(endPump, 0);
            output(UVPump, 0);

            output(ACInverter, 1);
            delay(1000);
            output(UVRelay, 0);
            #if !OVERRRIDEMAXVOLTAGE
                if (voltRead() < STOPWORKINGVOLTAGE)
                    mode = TRANSITIONTOIDLE;
            #endif

            waitForVoltage(STARTWORKINGVOLTAGE);
            pumpSt[3] = true;
            pumpPrevMillis[3] = millis();
            output(filterRelay, 1);

            mode = FILTERWORKING;
            break;
        case FILTERWORKING: // Filter Working
            #if !OVERRRIDEMAXVOLTAGE
                if (voltRead() < STOPWORKINGVOLTAGE)
                    mode = TRANSITIONTOIDLE;
            #endif

            if (digitalRead(highFilteredBuoy) || !digitalRead(lowSurfaceBuoy))
            {
                output(filterRelay, 0);
                pumpSt[3] = false;
                mode = TRANSITIONTOPUMPSWORKING;
            }
            break;
        }
    #endif

    #if GUI
        updateServer();
    #endif

    #if DEBUG
        perf = millis() - prevmillis;
    #endif
}

#if DEBUG
void readAllSensors()
{
    bool esecBuoy, elowSurfaceBuoy, ehighSurfaceBuoy, elowFilteredBuoy, ehighFilteredBuoy, elowPurifiedBuoy, ehighPurifiedBuoy, eendBuoy;
    esecBuoy = digitalRead(secBuoy);
    elowSurfaceBuoy = digitalRead(lowSurfaceBuoy);
    ehighSurfaceBuoy = digitalRead(highSurfaceBuoy);
    elowFilteredBuoy = digitalRead(lowFilteredBuoy);
    ehighFilteredBuoy = digitalRead(highFilteredBuoy);
    elowPurifiedBuoy = digitalRead(lowPurifiedBuoy);
    ehighPurifiedBuoy = digitalRead(highPurifiedBuoy);
    eendBuoy = digitalRead(endBuoy);

    float ACAmps;
    ACAmps = getACAmps();

    float temp[3];
#if TEMPERATURE
    getSensorsTemp(temp);
#endif
    bool escreenSensor;
#if GUI
    escreenSensor = digitalRead(screenSensor);
#endif
    1 + 1; //todo remove this :D
}
#endif
