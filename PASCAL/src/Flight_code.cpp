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


// Payload state stuff
int velocityInterval = 0;   // for check going down
int rangeInterval = 0;      // for check if stay constant
int thirtyTimer = 1800;  //30 minute timer(1800 second)initializing period
float oldAlt; //needed to check going up or down
int altitude = 0;

// TODO clean up this file

void setup() {

	Serial.begin(9600);
	initPins();
	initComponents();
	initLEDs();
    
	// TODO Remove this when we add it auotmatically in the class
  	// missing: nitrogen, WE, Aux,
	logger.write("Payload, Payload State, Sampling, Packet Number, Mission Time, SIV, "
		"UTC Time, Oxygen Concentration, Other Temp, Humidity, "
		"Temperature, Pressure, GPS Altitude, GPS Latitude, GPS Longitude"); 

}

void loop() {
	blinky(); 
	collectData();
  	logData();
	updateState();
	if (data.state == PASSIVE) controller.sampling();
}











