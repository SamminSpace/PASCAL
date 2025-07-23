// Keeps the linker from compiling this a bunch of times
#pragma once

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include "DFRobot_OxygenSensor.h"


// The I2C pins that all of the things will use
struct I2C {
    int sda = 12;
    int scl = 13;
};


// Where all of the pins go
struct Pins {

    int solenoidPins[6] = {
        2,
        3,
        4,
        5,
        6,
        9
    };
    int exhaustPin = 10;
    int pumpPin = 1;

    // The LEDs that will be flashing during the flight outside
    int brightLEDs = 11; 
    
    // These are the LEDs on the board, for debugging
    int tiny = 7;
    int smol = 8;
    int blinker;

    // For SPI I think
    int chipSelect = 17;

	// The I2C that everything uses
	I2C i2c;

};


// This is where you change the settings for each flight
struct Config {

    float samplingAltitudes[6] = {
        1000.0,
        3000.0,
        6000.0,
        9000.0,
        12000.0,
        15000.0
    }; // m

    float sampleLengths[6] = {
      250.0,	// 250
      500.0, 	// 500
      750.0, 	// 750
      1000.0,	// 1000
      1000.0, 	// 1000
      1250.0 	// 1250
    }; // ms

	// TODO Finalize these numbers
	float cleaningLengths[6] = {
		500.0,	// 500
		500.0, 	// 500
		500.0,	// 500
		500.0,	// 500
		500.0,	// 500
		500.0	// 500
	}; // ms

	// TODO Finalize these numbers
	float sealingLengths[6] = {
		250.0,	// 250
		250.0,	// 250
		250.0,	// 250
		250.0,	// 250
		250.0,	// 250
		250.0	// 250
	}; // ms
    
    Pins pins;

    // The constants, generally shouldn't be touched
    float seaLevelPressure = 1013.25;

    // Constants for the nitrogen sensor
    float WEOffset = 225;
    float AuxOffset = 224;
    float sensitivity = 0.225; //in mV/ppb
    // Technically depends on the temperature, so not constant
    int temperatureMultiplier = 1.3; 

	// Here in case we ever name it something different ig?
    String payload = "PASCAL";

};

