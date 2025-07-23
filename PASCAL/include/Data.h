#pragma once
#include <Arduino.h>

struct UTCTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct Position {
    double lon;  // DD.dddd
    double lat;  // DD.dddd
    double alt;  // m MSL
};

enum FlightState {
    INITIALIZATION = 0,
  	STANDBY = 1,
    PASSIVE = 2,
    DESCENT = 3,
    LANDED = 4,
};

// Numbered with the most important higher 
enum Error {
	NO_ERROR = 0,
	SD_ERROR = 9,
	GPS_ERROR = 10,
	BMP_ERROR = 2,
	NO2_ERROR = 6,
	HUMID_ERROR = 1,
	O2_ERROR = 3,
};


struct GPSData {
    Position pos;
    UTCTime time;
    int SIV;
};

// TODO Ensure these units match
struct Atmospheric {
    float pressure;     				// Pa?
    float temperature;  				// deg C?
    float alt;          				// m MSL
    double humidity;    				// percent
	double humiditySensorTemperature; 	// deg C?
	float oxygen;						// ppb
	float no2; 	    					// ppb
};

// Describes the samples as to whether they are running, done, or not started yet
enum class SampleState {
    NOT_STARTED = 0,
    ACTIVE = 1,
	CLEANING = 2,
    SEALING = 3,
    COMPLETE = 4
};



// The central data struct so that we can access everything
struct Data {
	unsigned long packetNumber = 0; 
	unsigned long missionTime = 0; // s
	FlightState state = FlightState::INITIALIZATION;
	SampleState sampleState = SampleState::NOT_STARTED;
	GPSData gpsData;
	Atmospheric atmoData;

	// For the no2 reading and debugging
	float WE_real; 	// mV 
	float Aux_real; // mV

    // The error code we are displaying
    Error error = NO_ERROR; // Yields the highest error generated
};