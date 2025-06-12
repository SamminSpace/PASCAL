

// All the includes 
#include "Config.h"
#include "Data.h"
#include "components/Logger.h"
#include "components/GPS.h"
#include "components/PumpController.h"


// Defining global variables
Config config;
Data data;
Logger logger = Logger("PASCAL");
GPS gps = GPS();
PumpController controller = PumpController();


// Sets the needed pins to be output or input
void initPins() {
	pinMode(config.pins.exhaustPin, OUTPUT);
	pinMode(config.pins.pumpPin, OUTPUT);
	pinMode(config.pins.brightLEDS, OUTPUT);
	pinMode(config.pins.tiny, OUTPUT);
	pinMode(config.pins.smol, OUTPUT);
	pinMode(config.pins.blinker, OUTPUT);
	pinMode(config.pins.WE1Pin, OUTPUT);
	pinMode(config.pins.Aux1Pin, OUTPUT);
	pinMode(config.pins.PTPin, OUTPUT);
	pinMode(config.pins.i2c.scl, OUTPUT);
	pinMode(config.pins.i2c.sda, OUTPUT);

	// Inits all solenoids, change the upper limit if adding more solenoids
	for (int i = 0; i < 6; i++) {
		pinMode(config.pins.solenoidPins[i], OUTPUT);
	}
}


// Function to get a string representations of the errors for printing
String getErrorString(Error error) {
	switch (error) {
		case SD_ERROR:
			if (error == SD_ERROR) {
				return "SD Error";
			}
		case GPS_ERROR:
			if (error == GPS_ERROR) {
				return "GPS error";
			}
		case BMP_ERROR:
			if (error == BMP_ERROR) {
				return "BMP Error"; 
			}
		case NO2_ERROR:
			if (error == NO2_ERROR) {
				return "Nitrogen Sensor Error";
			}
		case HUMID_ERROR:
			if (error == HUMID_ERROR) {
				return "Humidity Sensor Error";
			}
		case O2_ERROR:
			if (error == O2_ERROR) {
				return "Oxygen Sensor Error";
			}
		default:
			return "No Error";
	}	
}

// Function to get the sample state represented as a string for easy printing
String getSampleStateString(SampleState state) {

	String sampleStateStrs[] = {
		"Sample Not Active",
		"Sample Active",
		"Cleaning",
		"Sealing Sample",
		"Sample Not Active"
	};

	return sampleStateStrs[(int)state];
}

// Function to get the flight state represented as a string for easy printing
String getFlightStateString(FlightState state) {

	String flightStateStrs[] = {
		"Initialization",
		"Standby",
		"Passive",
		"Descending",
		"Landed"
	};

	return flightStateStrs[(int)state];
}

// woah a function that actually puts all the data in a massive string
void logData() { //future reference: nitrogen, Aux, WE
	data.missionTime = millis() / 1000.00;
    
	String Data = config.payload + ", " + 
	getFlightStateString(data.state) + ", " + 
	getSampleStateString(data.sampleState) + ", " +
	String(data.packetNumber) + ", " + 
	String(data.missionTime) + ", " + 
	String(data.gpsData.SIV) + ", " + 
	String(data.gpsData.time.year) + ":" + String(data.gpsData.time.month) + ":" + String(data.gpsData.time.day) + ":" + 
	String(data.gpsData.time.hour) + ":" + String(data.gpsData.time.minute) + ":" + String(data.gpsData.time.second) + ", " + 
	String() + ", " + 
	String(data.atmoData.temperature) + ", " + 
	String(data.atmoData.humidity) + ", " + 

	// We only have one temperature right now
	// String(bmp.getTemperature(SEALEVELPRESSURE_HPA)) + ", " +  

	String(data.atmoData.pressure) + ", " + 
	String(data.gpsData.pos.alt) + ", " + 
	String(data.gpsData.pos.lat) + ", " + 
	String(data.gpsData.pos.lon) +
	getErrorString(data.error);
	
	logger.write(Data);
  
	data.packetNumber++;

}
  