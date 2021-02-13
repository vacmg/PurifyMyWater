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

#define STARTCHARGINGVOLTAGE 13.5
#define STOPCHARGINGVOLTAGE 15.75
#define STARTWORKINGVOLTAGE 15
#define STOPWORKINGVOLTAGE 11

#define DCAmpSensivity 0.105 //sensor sensivity en Volts/Amps // 5.4A for 60w test load
#define DCAmpZero 2.469 // sensor voltage for 0 Amps current

#define ACAmpZero -0.0741 // sensor calibration correction value
#define ACAmpSensivity 0.0327 // sensor sensivity en Volts/Amps // 0.25A for 60w test load
#define ACFrequency 50 // test signal frequency (Hz)

#define TEMPCHECKTIME 1000
#define STOPWORKINGTEMP 65
#define MAXCASETEMP 40
#define MINCASETEMP 38
#define MAXPSUTEMP 40
#define MINPSUTEMP 38

/*------------Config----------------*/

/*------------Errors----------------*/

#define UNEXPECTEDBEHAVIORERROR 00 // The code is being executed in an unwanted way (a bug is being detected) // error code 00
#define TEMPSENSORSAMOUNTERROR 10 // Some temp sensors are not properly connected to the onewire bus // error code 10
#define EXTREMEHOTTEMPERROR 11 // Control system temperatures are extremely high and it is dangerous to operate // error code 11

/*------------Errors----------------*/

/*------------Const&vars------------*/

    /*------------Input-----------------*/

const byte voltSensor = A0;
const byte UVAmpSensor = A1;
const byte mainAmpSensor = A2;

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
}

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
float voltRead(byte vSensor)
{
    float f = fmap(analogRead(vSensor), 0, 1023, 0.0, 25.0);   // read from sensor and ajust the scale to 0-25V
    return f;
}

// This function maintains the voltage in the supercapacitors between STARTCHARGINGVOLTAGE and STOPCHARGINGVOLTAGE
// It MUST be called at least one time each 2 seconds
void voltControl()
{
    float voltage = voltRead(voltSensor);
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
    float voltage = voltRead(voltSensor);
    if (voltage < volts)
    {
        output(voltSSRelay, 1);
        while (voltage < volts)
        {
            voltage = voltRead(voltSensor);
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
    waitForVoltage(STARTCHARGINGVOLTAGE - 1);
    output(voltRelay, 0);

    // put setup code after this line

    inputStats.setWindowSecs(40.0 / ACFrequency);     //Set AC Amperemeter frequency

    setColor(CYAN);
}

// Add the main program code into the continuous loop() function

// temp vars (remove after debug)
unsigned long prevmillis, perf;
void loop()
{
    prevmillis = millis();

    voltControl();
    logACAmps();

    if (millis() > tempMillis + TEMPCHECKTIME)
    {
        tempControl();
        tempMillis = millis();
    }

    switch (mode)
    {
    case 0: // OFF

        break;
    case 1: // Pumps Working

        break;
    case 2: // Filter Working

        break;
    }

    perf = millis() - prevmillis;
}
