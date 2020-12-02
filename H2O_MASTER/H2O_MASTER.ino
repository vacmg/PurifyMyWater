// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     LEOPARD\Víctor
*/

// Define User Types below here or use a .h file
//
/*------------Config----------------*/
#define debug false
#define gui false
/*------------Config----------------*/

/*------------Const&vars------------*/

    /*------------Input-----------------*/
const byte secBuoy = 2;
const byte LowSurfaceBuoy = 3;
const byte HighSurfaceBuoy = 4;
const byte LowFilteredBuoy = 5;
const byte HighFilteredBuoy = 6;
const byte LowPurifiedBuoy = 7;
const byte HighPurifiedBuoy = 8;
const byte EndBuoy = 9;
const byte tempPin = 48;
#if gui
    const byte screenSensor = 23;
#endif
    /*------------Input-----------------*/

    /*------------Output----------------*/
    const byte voltSSRelay = 33;
    const byte voltRelay = 49;
    const byte ACInverter = 45;
    const byte wellPump = 43;
    const byte UVPump = 39;
    const byte endPump = 41;
    const byte UVRelay =37;
    const byte filterRelay = 35;
    const byte outFan = 22;
    const byte PSUFan = 24;
    const byte inFan = 26;
    const byte redLed = 10;
    const byte greenLed = 12;
    const byte blueLed = 11;
#if gui
    const byte screenRelay = 47;
#endif
    /*------------Output----------------*/

/*------------Const&vars------------*/



// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup()
{
#if debug
    Serial.begin(115200);
#endif
#if gui
    Serial1.begin(115200);
#endif

}

// Add the main program code into the continuous loop() function
void loop()
{


}
