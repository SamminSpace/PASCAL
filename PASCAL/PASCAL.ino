

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


// Declaring all of the sensors and things
Config config;  
// GPS gps; 
Logger sd = Logger((String("TestingWetness"))); 
BMP bmp;
HumiditySensor hum;

void setup() {

  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();

    // TODO finish the flight portion

    // Setting up the chipselect
    // pinMode(config.pins.chipSelect, OUTPUT);
    Serial.begin(9600);
    while (!Serial);

    // Initializing the things
    Serial.println("Beginning init");
    // if (gps.init() != NO_ERROR) {
    //   Serial.println("There was an error with the gps");
    // }
    if (sd.init(config.pins.chipSelect) != NO_ERROR) {
      Serial.println("There was an error with the SD");
    }
    if (bmp.init() != NO_ERROR) {
      Serial.println("There was an error with the bmp");
    }
    if (hum.init() != NO_ERROR) {
      Serial.println("There was an error with the bmp");
    }







}

void loop() {

  // First of all, testing the SD logging
  String position = String("");

  // position += String(gps.getAltitude()) + String(" meters altitude\n");
  // position += String(gps.getLatitude()) + String(" latitude\n");
  // position += String(gps.getLongitude()) + String(" longitude\n");
  // position += String(gps.getSIV()) + String(" sattelites locked\n");
  // position += String(gps.getUTCTime().hour) + String(" hours ") + gps.getUTCTime().minute + String(" minutes\n");

  // position += String("\nAltitude: ") + String(bmp.getAltitude(config.seaLevelPressureHPa));
  // position += String("\nPressure: ") + String(bmp.getPressure());
  // position += String("\nTemperature: ") + String(bmp.getTemperature());

  position += String("\nWetness: ") + String(hum.getWetness());


  sd.write(position);
  Serial.println(position.c_str());
  delay(1000);

}

