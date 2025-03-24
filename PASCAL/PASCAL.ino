

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


// Declaring all of the sensors and things
Config config;  
GPS gps; 
Logger sd = Logger((String("Testing")));  //probelms in config idk why

void setup() {
    Serial.begin(9600);

    // TODO finish the flight portion

    // Setting up the chipselect
    // pinMode(config.pins.chipSelect, OUTPUT);

    // Initializing the things
    // gps.init();
    sd.init(config.pins.chipSelect);

    pinMode(LED_BUILTIN, OUTPUT);




}

void loop() {

  // First of all, testing the SD logging
  sd.write("Watermelon");
  Serial.write("Printing out watermelon");

  digitalWrite(LED_BUILTIN, HIGH)

}

