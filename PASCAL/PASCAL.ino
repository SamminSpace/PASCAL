
// This is what Arduino IDE will actually be running
// Everything else will be imported

// Library imports
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include "DFRobot_OxygenSensor.h"

// Sensor imports
#import "Include/Logger.h"
#import "Include/BMP.h"
#import "Include/Oxygen.h"
#import "Include/GPS.h"
#import "Config.h"


// Declaring all of the sensors and things
Config config;
GPS gps
Logger sd("Testing");

void setup() {

    // Setting up the chipselect
    pinMode(config.pins.chipSelect, OUTPUT);

    // Initializing the things
    gps.init();
    sd.init();
    



}

void loop() {



}

