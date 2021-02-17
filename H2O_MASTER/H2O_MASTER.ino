// Visual Micro
// 
/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

// Define used Libraries below here or use a .h file
//

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Filters.h>

// Define User Types below here or use a .h file
//

/*------------Config----------------*/

#define GUI false
#define ONLYVITALACTIVITYALLOWED false
#define TEMPERATURE true

#define STARTCHARGINGVOLTAGE 13
#define STOPCHARGINGVOLTAGE 15.75
#define STARTWORKINGVOLTAGE 15
#define STOPWORKINGVOLTAGE 12

#define DCAmpSensivity 0.1135 //sensor sensivity en Volts/Amps // 5.4A for 60w test load
#define DCAmpZero 2.4956 // sensor voltage for 0 Amps current

#define ACAmpZero -0.07157 // sensor calibration correction value
#define ACAmpSensivity 0.033 // sensor sensivity en Volts/Amps // 0.25A for 60w test load
#define ACFrequency 50 // test signal frequency (Hz)

#if TEMPERATURE
    #define TEMPCHECKTIME 10000
    #define STOPWORKINGTEMP 65
    #define MAXCASETEMP 40
    #define MINCASETEMP 38
    #define MAXPSUTEMP 40
    #define MINPSUTEMP 38
#endif

/*------------Config----------------*/

/*------------Errors----------------*/

#define UNEXPECTEDBEHAVIORERROR 00 // The code is being executed in an unwanted way (a bug is being detected) // error code 00
#define TEMPSENSORSAMOUNTERROR 10 // Some temp sensors are not properly connected to the onewire bus // error code 10

#if TEMPERATURE
    #define EXTREMEHOTTEMPERROR 11 // Control system temperatures are extremely high and it is dangerous to operate // error code 11endif
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
const byte screenSensor = 23;
#endif

RunningStatistics inputStats;                 // create statistics to look at the raw test signal
bool ACAmpsDoMeasurement = false; // boolean value used as a switch to begin measuring AC current

    /*------------Input-----------------*/

    /*------------Output----------------*/

#define BLACK 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define YELLOW 5
#define CYAN 6
#define PURPLE 7

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

byte mode = 0; // working mode is changed using this variable

    /*------------Other-----------------*/

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

// Used to control the temperature of the main control 
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

    /*output(inFan, 1);
    output(outFan, 1);
    output(PSUFan, 1);//*/
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
void setColor(byte r, byte g, byte b)
{
    analogWrite(redLed, r);
    analogWrite(greenLed, g);
    analogWrite(blueLed, b);
}

// Used to set a color on the rgb status led using a predefined color
void setColor(byte color)
{
    switch (color)
    {
    case RED:
        output(redLed, 1);
        output(greenLed, 0);
        output(blueLed, 0);
        break;
    case GREEN:
        output(redLed, 0);
        output(greenLed, 1);
        output(blueLed, 0);
        break;
    case BLUE:
        output(redLed, 0);
        output(greenLed, 0);
        output(blueLed, 1);
        break;
    case WHITE:
        output(redLed, 1);
        output(greenLed, 1);
        output(blueLed, 1);
        break;
    case YELLOW:
        output(redLed, 1);
        output(greenLed, 1);
        output(blueLed, 0);
        break;
    case CYAN:
        output(redLed, 0);
        output(greenLed, 1);
        output(blueLed, 1);
        break;
    case PURPLE:
        output(redLed, 1);
        output(greenLed, 0);
        output(blueLed, 1);
        break;
    case BLACK:
    default:
        output(redLed, 0);
        output(greenLed, 0);
        output(blueLed, 0);
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
void waitForVoltage(int volts)
{
    float voltage = voltRead();
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
    return(corriente);
}

// This function uses all the data logged by logACAmps() and calculates an RMS Amperage value
float getACAmps()
{
    return(ACAmpZero + ACAmpSensivity * inputStats.sigma()); // calculate RMS Amperage
}

// To measure AC current, arduino must log sensor data all the time. This function read and log one value per call
void logACAmps()
{
    inputStats.input(analogRead(UVAmpSensor));  // log to Stats function
}

/*------------Amperage Control----------*/

/*------------Exceptions Control--------*/

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function
// This function is not completed yet
void raise(byte error, String possibleExplanation)
{
    setColor(RED);
    Serial.print(F("Error "));
    Serial.print(error);
    Serial.print(F(": "));
    Serial.println(possibleExplanation);
    while (true)
    {
        voltControl();
    }
}

/*------------Exceptions Control--------*/

// The setup() function runs once each time the micro-controller starts
void setup()
{
  Serial.begin(115200);
  
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);

    setColor(YELLOW);

    sensors.begin();
    if (sensors.getDeviceCount() < 3)
    {
        raise(TEMPSENSORSAMOUNTERROR, String(F("Less than 3 sensors were connected.\nNumber of sensors detected: "))+String(sensors.getDeviceCount()));
    }

    pinMode(secBuoy, INPUT);
    pinMode(lowSurfaceBuoy, INPUT);
    pinMode(highSurfaceBuoy, INPUT);
    pinMode(lowFilteredBuoy, INPUT);
    pinMode(highFilteredBuoy, INPUT);
    pinMode(lowPurifiedBuoy, INPUT);
    pinMode(highPurifiedBuoy, INPUT);
    pinMode(endBuoy, INPUT);
    pinMode(tempPin, INPUT);

    pinMode(voltSSRelay, OUTPUT);
    pinMode(voltRelay, OUTPUT);
    pinMode(ACInverter, OUTPUT);
    pinMode(wellPump, OUTPUT);
    pinMode(UVPump, OUTPUT);
    pinMode(endPump, OUTPUT);
    pinMode(UVRelay, OUTPUT);
    pinMode(filterRelay, OUTPUT);
    pinMode(outFan, OUTPUT);
    pinMode(PSUFan, OUTPUT);
    pinMode(inFan, OUTPUT);

    output(voltSSRelay, 0);
    output(voltRelay, 1);
    output(ACInverter, 0);
    output(wellPump, 0);
    output(UVPump, 0);
    output(endPump, 0);
    output(UVRelay, 0);
    output(filterRelay, 0);
    output(outFan, 1);
    output(PSUFan, 1);
    output(inFan, 1);

#if GUI
    pinMode(screenSensor, INPUT);
    pinMode(screenRelay, OUTPUT);
    output(screenRelay, 0);

    Serial1.begin(115200);
#endif
#if !ONLYVITALACTIVITYALLOWED
    #if TEMPERATURE
        tempControl();
    #endif
    waitForVoltage(STARTCHARGINGVOLTAGE - 1);
#endif
    output(voltRelay, 0);

    // put setup code after this line

    inputStats.setWindowSecs(40.0 / ACFrequency);     //Set AC Amperemeter frequency

    mode = 0;
}

// Add the main program code into the continuous loop() function

// temp vars (remove after debug)
unsigned long prevmillis, perf;

bool pumpSt[3] = { false, false, false }; // Used to store the status of each pump where true is on and false is off

void loop()
{
    prevmillis = millis();

    voltControl();
    logACAmps();

    #if TEMPERATURE
        if (millis() > tempMillis + TEMPCHECKTIME)
        {
            tempControl();
            tempMillis = millis();
        }
    #endif
    // readAllSensors(); // temporal debug function

    #if ONLYVITALACTIVITYALLOWED
    setColor(WHITE);
    #else
    switch (mode)
    {
    case 0: // Transition to OFF
        output(wellPump, 0);
        output(endPump, 0);
        output(UVPump, 0);
        output(filterRelay, 0);
        output(ACInverter, 0);
        delay(1000);
        output(UVRelay, 0);
        output(voltSSRelay, 1);
        setColor(PURPLE);
        mode = 1;
        break;
    case 1: // OFF
        if (voltRead() > STARTWORKINGVOLTAGE)
            mode = 2;
        break;
    case 2: // Transition to Pumps Working
        output(ACInverter, 0);
        setColor(CYAN);
        for (byte i = 0; i < 3; i++)
        {
            pumpSt[i] = false;
        }
        mode = 3;
        break;
    case 3: // Pumps Working
        if (voltRead() < STOPWORKINGVOLTAGE)
            mode = 0;

        if (!pumpSt[0] && !digitalRead(highSurfaceBuoy) && digitalRead(secBuoy))
        {
            output(wellPump, 1);
            pumpSt[0] = true;
        }
            

        if (pumpSt[0] && (digitalRead(highSurfaceBuoy) || !digitalRead(secBuoy)))
        {
            output(wellPump, 0);
            pumpSt[0] = false;
        }
            

        if (!digitalRead(lowFilteredBuoy) && digitalRead(highSurfaceBuoy))
            mode = 4;

        if (!pumpSt[1] && !digitalRead(highPurifiedBuoy) && digitalRead(lowFilteredBuoy))
        {
            output(ACInverter, 1);
            delay(250);
            output(UVRelay, 1);
            delay(1000);
            output(UVPump, 1);
            pumpSt[1] = true;
        }

        if (pumpSt[1] && (!digitalRead(lowFilteredBuoy) || digitalRead(highPurifiedBuoy)))
        {
            output(UVPump, 0);
            delay(1000);
            output(UVRelay, 0);
            delay(250);
            output(ACInverter, 0);
            pumpSt[1] = false;
        }

        if (!pumpSt[2] && !digitalRead(endBuoy) && digitalRead(lowPurifiedBuoy))
        {
            output(endPump, 1);
            pumpSt[2] = true;
        }

        if (pumpSt[2] && (!digitalRead(lowPurifiedBuoy) || digitalRead(endBuoy)))
        {
            output(endPump, 0);
            pumpSt[2] = false;
        }

        break;
    case 4: // Transition to filter working
        output(wellPump, 0);
        output(endPump, 0);
        output(UVPump, 0);

        output(ACInverter, 1);
        delay(1000);
        output(UVRelay, 0);

        if (voltRead() < STOPWORKINGVOLTAGE)
            mode = 0;

        waitForVoltage(STARTWORKINGVOLTAGE);
        output(filterRelay, 1);

        mode = 5;
        break;
    case 5: // Filter Working
        if (voltRead() < STOPWORKINGVOLTAGE) // quizas haya que quitar esto o poner un while...
            mode = 0;

        if (digitalRead(highFilteredBuoy) || !digitalRead(lowSurfaceBuoy))
        {
            output(filterRelay, 0);
            mode = 2;
        }
        break;
    }
    #endif
    
    perf = millis() - prevmillis;
}

/*********Debug*************
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
#if TEMPERATURE
    float temp[3];
    getSensorsTemp(temp);
#endif
#if GUI
    bool escreenSensor;
    escreenSensor = digitalRead(screenSensor);
#endif
    1 + 1;
}
/*********Debug*************/
