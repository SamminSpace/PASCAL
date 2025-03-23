
// This is what Arduino IDE will actually be running
// Everything else will be imported

// Library imports
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include "DFRobot_OxygenSensor.h"

// Sensor imports
#include "Logger.h"
#include "BMP.h"
#include "Oxygen.h"
#include "GPS.h"
#include "Config.h"


// Declaring all of the sensors and things
Config config;  
GPS gps; //had to comment out Timer in line 18 of gps.h to config
Logger sd = Logger((String("Testing")));  //probelms in config idk why

void setup() {
    // TODO finish the flight portion

    // Setting up the chipselect
    // pinMode(config.pins.chipSelect, OUTPUT);

    // Initializing the things
    // gps.init();
    // sd.init();
    



}

void loop() {

}

