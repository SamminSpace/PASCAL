// This is what Arduino IDE will actually be running
// Everything else will be imported

#include "Arduino.h"
#include "Data.h"
#include "Config.h"
#include "PASCAL.h"

// Library imports
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 
#include "DFRobot_OxygenSensor.h"

// Sensor imports
#include "components/Logger.h"
#include "components/BMP.h"
#include "components/Oxygen.h"
#include "components/GPS.h"
#include "Config.h"
#include "components/Humidity.h"
#include "components/PumpController.h"


// Pre-declaring the functions
void Blinky();
void checkErrors(Error error);
void logData();
bool isConstantAlt();
bool isItDescending();
void decideState();


// Payload state stuff
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
	pinMode(config.pins.brightLEDS, OUTPUT);

	// Initializes solenoids/motor
	controller.init();
		
    Serial.begin(9600);


    // Initializing the things
    humidity.turnOn();
    oxygen.init();
    bmp.init();
    gps.init();
	logger.init();

    pinMode(LED_BUILTIN, OUTPUT);

    
	// TODO Remove this when we add it auotmatically in the class
  	// missing: nitrogen, WE, Aux,
	logger.write("Payload, Payload State, Sampling, Packet Number, Mission Time, SIV, "
		"UTC Time, Oxygen Concentration, Other Temp, Humidity, "
		"Temperature, Pressure, GPS Altitude, GPS Latitude, GPS Longitude"); 

	data.state = INITIALIZATION;
}

void loop() {
  Blinky(); //must be in loop 


 
  logData();

//   if (tock.isComplete()) {
//     decideState();
//     tock.reset();
//   }

//   if(flightState == INITIALIZATION){
//     controller.pattern();
//     initializeLEDS();
//   }  
//   else if(flightState == PASSIVE){
//     controller.sampling(altitude);
//   } 

}




void decideState() // TODO Run this every 15 seconds
{
  
    if ((data.missionTime > thirtyTimer) && (data.state == INITIALIZATION)) // No timer yet so removing it for testing + not needed for this flight
    {
        data.state = STANDBY;
    
    }
    else if ((altitude > 500) && (data.state == STANDBY))
    {
        data.state = PASSIVE;
      	
    }
    else if ((isItDescending()) && (data.state == PASSIVE))
    {
        data.state = DESCENT;
      
      
    }
    else if ((isConstantAlt()) && (data.state == DESCENT) && altitude < 500){
    
        data.state = LANDED;
  
    }

    oldAlt = altitude;
}


bool isItDescending() {

    if (altitude  < oldAlt) {

        velocityInterval++;
        Serial.println("going down?!!!!");

        if (velocityInterval > 3) // If it descends for over a minute it changes the state to Descending
        {
            velocityInterval = 0; 
            Serial.println("HEY IT SHOULD BE TRUE FOR NEGATIVE VELOCITY!");
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



bool isConstantAlt() {

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
void checkErrors(Error error) {


switch(error){		
    case SD_ERROR:  //error 1 will be SD (all on)
      config.pins.blinker = LED_BUILTIN; 
        //digitalWrite(config.pins.tiny, HIGH);
        //digitalWrite(config.pins.smol, HIGH);
        config.pins.blinker = LED_BUILTIN;   //IF SD ERROR PICO LED BLINKS
        break;
    
    case GPS_ERROR:  //error 2 is GPS (1 on/off)
        logger.write("Hey, your GPS is messed up!");
        //digitalWrite(config.pins.tiny, HIGH);
        //digitalWrite(config.pins.smol, LOW);
        break;
    
    case BMP_ERROR:   //BMP (other on/off)
        logger.write("BMP not found.");
        //digitalWrite(config.pins.tiny, LOW);
        //digitalWrite(config.pins.smol, HIGH);
        break;
    
    case NO2_ERROR:  // NO2 (tiny blinks and smol on)
        logger.write("NO2 (the problem child) is not functioning");
        //digitalWrite(config.pins.smol, HIGH);
        //config.pins.blinker = config.pins.tiny;
        // Blinky();
        break;
    
    case HUMID_ERROR:  //Humidity (smol blinks and tiny on)
        logger.write("Must be too dry bc humidity not detected.");
        //digitalWrite(config.pins.tiny, HIGH);
        //config.pins.blinker = config.pins.smol;
        // Blinky();
        break;
     
    case O2_ERROR:   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
        logger.write("Apparently no oxygen found so idk how you are alive rn");
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
 
  // TODO Replace this with a timer
//   if (currentMillis - beginMillis >= period)  //test whether the period has elapsed
//   {
//     digitalWrite(config.pins.blinker, !digitalRead(config.pins.blinker));
//     if (data.state != INITIALIZATION){
//       digitalWrite(config.pins.brightLEDS, !digitalRead(config.pins.brightLEDS));  // blinking likes go blink
//        Serial.println("NORMAL");
//     }  
//     beginMillis = currentMillis;  //save the start time of the current LED state.
//   } 
}


