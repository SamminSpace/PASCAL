

// This is what Arduino IDE will actually be running
// Everything else will be imported

// Library imports
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 
#include "DFRobot_OxygenSensor.h"

// Sensor imports
#include "Logger.h"
#include "BMP.h"
#include "Oxygen.h"
#include "GPS.h"
#include "Config.h"
#include "Humidity.h"
#include "PumpController.h"


// Declaring all of the sensors and things
Config config;  
GPS gps; 
HumiditySensor humidity;
BMP bmp;
OxygenSensor oxygen;
PumpController controller(config);
Logger sd = Logger((String("NoOxygen")));  //probelms in config idk why

//Error Code Stuff
errorState error;
unsigned long beginMillis;
int period = 500;
void Blinky() {
  unsigned long currentMillis;
  
  currentMillis = millis();  
  if (currentMillis - beginMillis >= period)  //test whether the period has elapsed
  {
    digitalWrite(config.pins.blinker, !digitalRead(config.pins.blinker));
    digitalWrite(config.pins.brightsLEDS, !digitalRead(config.pins.brightsLEDS));  // blinkingh likes go blink
    beginMillis = currentMillis;  //save the start time of the current LED state.
  } 
}

//payload state stuff
State flightState;
int velocityInterval = 0;   // for check going down
int rangeInterval = 0;      // for check if stay constant
int thirtyTimer = 10000;  // TEMP 10 SEC for 30 minute timer(1800000 miliseconds)initializing period
float oldAlt; //needed to check going up or down


void setup() {

  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();

    // TODO finish the flight portion

    // Setting up the chipselect
    pinMode(config.pins.chipSelect, OUTPUT);
    pinMode(config.pins.tiny, OUTPUT);
    pinMode(config.pins.smol, OUTPUT);
    pinMode(config.pins.brightsLEDS, OUTPUT);

    controller.init();
    
    /*pinMode(config.pins.solenoidPins[0], OUTPUT);
    pinMode(config.pins.solenoidPins[1], OUTPUT);
    pinMode(config.pins.solenoidPins[2], OUTPUT);
    pinMode(config.pins.solenoidPins[3], OUTPUT);
    pinMode(config.pins.solenoidPins[4], OUTPUT);
    pinMode(config.pins.solenoidPins[5], OUTPUT);
    pinMode(config.pins.exhaustPin, OUTPUT);
    pinMode(config.pins.pumpPin, OUTPUT); */

    Serial.begin(9600);
    while (!Serial); //will need removal

    // Initializing the things
    // error = humidity.turnOn();
    // error = oxygen.init();
    // error = bmp.init();
    // error = gps.init();
    // error = sd.init(config.pins.chipSelect);

    pinMode(LED_BUILTIN, OUTPUT);

    switch(error){		//error 1 will be SD (all on)
    case SD_ERROR:
    digitalWrite(config.pins.tiny, HIGH);
    digitalWrite(config.pins.smol, HIGH);
    break;
    
    case GPS_ERROR:  //error 2 is GPS (1 on/off)
    sd.write("Hey, your GPS is messed up!");
    digitalWrite(config.pins.tiny, HIGH);
    digitalWrite(config.pins.smol, LOW);
    break;
    
    case BMP_ERROR:   //BMP (other on/off)
    sd.write("BMP not found.");
    digitalWrite(config.pins.tiny, LOW);
    digitalWrite(config.pins.smol, HIGH);
    break;
    
    case NO2_ERROR:  // NO2 (tiny blinks and smol on)
    sd.write("NO2 (the problem child) is not functioning");
    digitalWrite(config.pins.smol, HIGH);
    config.pins.blinker = config.pins.tiny;
    Blinky();
    break;
    
    case HUMID_ERROR:  //Humidity (smol blinks and tiny on)
    sd.write("Must be too dry bc humidty not detected.");
    digitalWrite(config.pins.tiny, HIGH);
    config.pins.blinker = config.pins.smol;
    Blinky();
    break;
     
    case O2_ERROR:   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
    sd.write("Apparently no oxygen found so idk how you are alive rn");
    digitalWrite(config.pins.tiny, LOW);
    config.pins.blinker = config.pins.smol;
    Blinky();
    break;
      
    default:
    sd.write("lets go!");
    digitalWrite(config.pins.tiny, LOW);
    digitalWrite(config.pins.smol, LOW);
  }

  // missing: nitrogen, WE, Aux, BMP Alt
  sd.write("Payload, Payload State, Packet Number, Mission Time, SIV, "
    "UTC Time, Oxygen Concentration, Other Temp, Humidity, "
    "Temperature, Pressure, GPS Altitude, GPS Laitiude, GPS Longitude");  

}

void loop() {
  // Blinky(); //must be in loop

 

  //digitalWrite(config.pins.solenoidPins[0], HIGH);
  decideState();
  /*Serial.print("   SOLENOID 1: ");
  Serial.println(digitalRead(config.pins.solenoidPins[0]));
  Serial.print("   SOLENOID 2: ");
  Serial.println(digitalRead(config.pins.solenoidPins[1]));
  Serial.print("   PUMP: ");
  Serial.println(digitalRead(config.pins.pumpPin));
  Serial.print("   EXHAUST: ");
  Serial.println(digitalRead(config.pins.exhaustPin)); */
  if(flightState == PASSIVE){
    controller.sampling(gps.getAltitude());
  }
  
 

  //Deciding what payload state in 
  //Need to put the timer part in here
  //decideState();


}

// woah a function that actually puts all the data in a massive string
void logData (){ //future reference: nitrogen, Aux, WE
  config.missionTime = millis();

  String Data = config.payload + ", " + 
  flightState + ", " + 
  String(config.packetNumber) + ", " + 
  String(config.missionTime) + ", " + 
  String(gps.getSIV()) + ", " + 
  "UTC TIME" + ", " +
  
  String(oxygen.getOxygen()) + ", " + 
  String(humidity.getHotness()) + ", " + 
  String(humidity.getWetness()) + ", " + 
  String(bmp.getTemperature()) + ", " + 
  String(bmp.getPressure()) + ", " + 
  String(gps.getAltitude()); + ", " + 
  String(gps.getLatitude()) + ", " + 
  String(gps.getLongitude());
  
  sd.write(Data);

  config.packetNumber ++;
}



void decideState() // TODO Run this every 15 seconds
{
  
    if ((config.missionTime > thirtyTimer) && (flightState == INITIALIZATION)) // No timer yet so removing it for testing + not needed for this flight
    {
        flightState = STANDBY;
    
    }
    else if ((gps.getAltitude() > 500) && (flightState == STANDBY))
    {
        flightState = PASSIVE;
      	
    }
    else if ((isItDescending()) && (flightState == PASSIVE))
    {
        flightState = DESCENT;
      
      
    }
    else if ((isConstantAlt()) && (flightState == DESCENT) && gps.getAltitude() < 20)
    {
        flightState = LANDED;
  
    }
}


bool isItDescending()
{
    if (gps.getAltitude() < oldAlt)
    {
        velocityInterval++;
        Serial.println("going down?!!!!");

        if (velocityInterval > 4) // If it descends for over a minute it changes the state to Descending
        {
            velocityInterval = 0; 
            Serial.println("HEY IT SHOULD BE TRUE FOR NEGATIVE VELOCOTY!");
            return true;
        }
    }
    else
    {
        velocityInterval = 0;
        return false;
    }
    return false;
}



bool isConstantAlt()
{
  if ((gps.getAltitude() < oldAlt + 20) && (gps.getAltitude() > oldAlt - 20)) //Checks if payload stationary
    {
        rangeInterval++;
        if (rangeInterval > 4) // If it stays within +-50 Meters for over a minute it changes the state to Landed
        {
            rangeInterval = 0; 
            return true;
        }
    }
    else
    {
        rangeInterval = 0;
        return false;
    }

    return false;
 }



