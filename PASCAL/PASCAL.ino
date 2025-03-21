
// This is what Arduino IDE will actually be running
// Everything else will be imported

// Library imports
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include "DFRobot_OxygenSensor.h"

// Sensor imports
#import "Logger.h"
#import "BMP.h"
#import "Oxygen.h"
#import "GPS.h"
#import "Config.h"


// Declaring all of the sensors and things
Config config;  
GPS gps;
Logger sd = Logger((String("Testing")));

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

