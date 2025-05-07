
#define SEALEVELPRESSURE_HPA (1013.25)
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
UTCTime utctime;
HumiditySensor humidity;
BMP bmp;
OxygenSensor oxygen;
PumpController controller(config);
Timer tock = Timer(15000); //15 second timer
Logger sd = Logger((String("NightFlight")));  

// Debugging stuff
Timer fakeAltitudeTimer(16000);

//Error Code Stuff
errorState error;
unsigned long beginMillis;
int period = 500;

//for external Leds
unsigned long beginTime;
bool ledOn;

void initializeLEDS() {
  unsigned long currentTime;
  currentTime = millis(); 

  if (!ledOn && (currentTime - beginTime >= 5000)) {
    digitalWrite(config.pins.brightsLEDS, HIGH);
    ledOn = true;
    beginTime = currentTime;
     Serial.println("LEDS ON");
  }

  if (ledOn && (currentTime - beginTime >= 100)) {
    digitalWrite(config.pins.brightsLEDS, LOW);
     Serial.println("OFF");
    ledOn = false;
  }
 
}



//payload state stuff
State flightState;
int velocityInterval = 0;   // for check going down
int rangeInterval = 0;      // for check if stay constant
int thirtyTimer = 1800;  //30 minute timer(1800 second)initializing period
float oldAlt; //needed to check going up or down
int altitude = 0;

void setup() {

  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();

   // Setting up the chipselect
  pinMode(config.pins.chipSelect, OUTPUT);
  pinMode(config.pins.tiny, OUTPUT);
  pinMode(config.pins.smol, OUTPUT);
  pinMode(config.pins.brightsLEDS, OUTPUT);

  // Initializes solenoids/motor
  controller.init();
    
    Serial.begin(9600);


    // Initializing the things
    checkErrors(humidity.turnOn());
    checkErrors(oxygen.init());
    checkErrors(bmp.init());
    checkErrors(gps.init());
    checkErrors(sd.init(config.pins.chipSelect));

    pinMode(LED_BUILTIN, OUTPUT);

    

  // missing: nitrogen, WE, Aux,
  sd.write("Payload, Payload State, Sampling, Packet Number, Mission Time, SIV, "
    "UTC Time, Oxygen Concentration, Other Temp, Humidity, "
    "Temperature, Pressure, GPS Altitude, GPS Latitude, GPS Longitude"); 

  flightState = INITIALIZATION;
}

void loop() {
  Blinky(); //must be in loop 


   // Updating the altitude if lock 
  if (gps.getSIV() >= 3){
    digitalWrite(LED_BUILTIN, HIGH);
    altitude = gps.getAltitude();
  } else {
    altitude = -1;
  }
  
 
  logData();

  /* Updating the altitude to the right stuff
  if (fakeAltitudeTimer.isComplete()) {
    altitude += 1000;
    fakeAltitudeTimer.reset();
    //Serial.print("Moved up 1000 meters; altitude is now ");
    //Serial.println(altitude);
  } */

  
  //Serial.println(altitude);
  //Serial.println(flightState);
  
  if (tock.isComplete()) {
    decideState();
    tock.reset();
  }

  if(flightState == INITIALIZATION){
    controller.pattern();
    initializeLEDS();
  }  
  else if(flightState == PASSIVE){
    controller.sampling(altitude);
  } 

}

// woah a function that actually puts all the data in a massive string
void logData (){ //future reference: nitrogen, Aux, WE
  config.missionTime = millis() / 1000.00;

  utctime = gps.getUTCTime();

  String Data = config.payload + ", " + 
  flightState + ", " + 
  controller.getSampleStatus() + ", " +
  String(config.packetNumber) + ", " + 
  String(config.missionTime) + ", " + 
  String(gps.getSIV()) + ", " + 
  String(utctime.year) + ":" + String(utctime.month) + ":" + String(utctime.day) + ":" + 
  String(utctime.hour) + ":" + String(utctime.minute) + ":" + String(utctime.second) + ", " + 
  String(oxygen.getOxygen()) + ", " + 
  String(humidity.getHotness()) + ", " + 
  String(humidity.getWetness()) + ", " + 
  String(bmp.getTemperature(SEALEVELPRESSURE_HPA)) + ", " + 
  String(bmp.getPressure(SEALEVELPRESSURE_HPA)) + ", " + 
  String(altitude) + ", " + 
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
    else if ((altitude > 500) && (flightState == STANDBY))
    {
        flightState = PASSIVE;
      	
    }
    else if ((isItDescending()) && (flightState == PASSIVE))
    {
        flightState = DESCENT;
      
      
    }
    else if ((isConstantAlt()) && (flightState == DESCENT) && altitude < 500){
    
        flightState = LANDED;
  
    }

    oldAlt = altitude;
}


bool isItDescending()
{
    if (altitude  < oldAlt)
    {
        velocityInterval++;
        Serial.println("going down?!!!!");

        if (velocityInterval > 3) // If it descends for over a minute it changes the state to Descending
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
  if ((altitude  < oldAlt + 20) && (altitude  > oldAlt - 20)) //Checks if payload stationary
    {
        rangeInterval++;
        if (rangeInterval > 3) // If it stays within +-50 Meters for over a minute it changes the state to Landed
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


// Function to check for errors and display error codes
void checkErrors(errorState error) {


switch(error){		
    case SD_ERROR:  //error 1 will be SD (all on)
      config.pins.blinker = LED_BUILTIN; 
        //digitalWrite(config.pins.tiny, HIGH);
        //digitalWrite(config.pins.smol, HIGH);
        config.pins.blinker = LED_BUILTIN;   //IF SD ERROR PICO LED BLINKS
        break;
    
    case GPS_ERROR:  //error 2 is GPS (1 on/off)
        sd.write("Hey, your GPS is messed up!");
        //digitalWrite(config.pins.tiny, HIGH);
        //digitalWrite(config.pins.smol, LOW);
        break;
    
    case BMP_ERROR:   //BMP (other on/off)
        sd.write("BMP not found.");
        //digitalWrite(config.pins.tiny, LOW);
        //digitalWrite(config.pins.smol, HIGH);
        break;
    
    case NO2_ERROR:  // NO2 (tiny blinks and smol on)
        sd.write("NO2 (the problem child) is not functioning");
        //digitalWrite(config.pins.smol, HIGH);
        //config.pins.blinker = config.pins.tiny;
        // Blinky();
        break;
    
    case HUMID_ERROR:  //Humidity (smol blinks and tiny on)
        sd.write("Must be too dry bc humidty not detected.");
        //digitalWrite(config.pins.tiny, HIGH);
        //config.pins.blinker = config.pins.smol;
        // Blinky();
        break;
     
    case O2_ERROR:   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
        sd.write("Apparently no oxygen found so idk how you are alive rn");
        //digitalWrite(config.pins.tiny, LOW);
        //config.pins.blinker = config.pins.smol;
        // Blinky();
        break;
      
    default:
        //sd.write("lets go!");
        //digitalWrite(config.pins.tiny, LOW);
        //digitalWrite(config.pins.smol, LOW);
        digitalWrite(LED_BUILTIN, LOW);
  }


}


void Blinky() {
  unsigned long currentMillis;
  currentMillis = millis(); 
 
  if (currentMillis - beginMillis >= period)  //test whether the period has elapsed
  {
    digitalWrite(config.pins.blinker, !digitalRead(config.pins.blinker));
    if (flightState != INITIALIZATION){
      digitalWrite(config.pins.brightsLEDS, !digitalRead(config.pins.brightsLEDS));  // blinking likes go blink
       Serial.println("NORMAL");
    }  
    beginMillis = currentMillis;  //save the start time of the current LED state.
  } 
}


