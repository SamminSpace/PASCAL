

// All the includes 
#include "Config.h"
#include "Data.h"
#include "Timers.h"
#include "components/Logger.h"
#include "components/GPS.h"
#include "components/PumpController.h"
#include "components/Humidity.h"
#include "components/BMP.h"
#include "components/Oxygen.h"
#include "components/Nitrogen.h"


// Defining global variables
Config config;
Data data;
Logger logger = Logger("PASCAL");
GPS gps = GPS();
PumpController controller = PumpController();
HumiditySensor humidity = HumiditySensor();
BMP bmp = BMP();
OxygenSensor oxygen = OxygenSensor();
NO2Sensor no2 = NO2Sensor();


// Sets the needed pins to be output or input
void initPins() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(config.pins.exhaustPin, OUTPUT);
	pinMode(config.pins.pumpPin, OUTPUT);
	pinMode(config.pins.brightLEDs, OUTPUT);
	pinMode(config.pins.tiny, OUTPUT);
	pinMode(config.pins.smol, OUTPUT);
	pinMode(config.pins.blinker, OUTPUT);
	pinMode(config.pins.i2c.scl, OUTPUT);
	pinMode(config.pins.i2c.sda, OUTPUT);

	// Inits all solenoids, change the upper limit if adding more solenoids
	for (int i = 0; i < 6; i++) {
		pinMode(config.pins.solenoidPins[i], OUTPUT);
	}

	Wire.setSDA(12);
	Wire.setSCL(13);
	Wire.begin();

}

void initComponents() {
	logger.init();
	gps.init();
	humidity.turnOn();
	bmp.init();
	oxygen.init();
	no2.init(config.WEOffset, config.AuxOffset, config.sensitivity, config.temperatureMultiplier);
	controller.init();
}

// Turns on all of the LEDs to ensure they are operational
void initLEDs(int msDelay) {
	
	digitalWrite(config.pins.brightLEDs, HIGH);
	digitalWrite(config.pins.tiny, HIGH);
	digitalWrite(config.pins.smol, HIGH);
	digitalWrite(config.pins.blinker, HIGH); // I'm not entirely sure what this is?
	delay(msDelay);
	digitalWrite(config.pins.brightLEDs, LOW);
	digitalWrite(config.pins.tiny, LOW);
	digitalWrite(config.pins.smol, LOW);
	digitalWrite(config.pins.blinker, LOW);

}

// Timer that blinks the external LEDs throughout the flight
Timer blinkyTimer = Timer(500); // Half a second

void blinky() {
	if (blinkyTimer.isComplete()) {
		digitalWrite(config.pins.blinker, !digitalRead(config.pins.blinker));
		if (data.state != INITIALIZATION){
			digitalWrite(config.pins.brightLEDs, !digitalRead(config.pins.brightLEDs));
		}
		blinkyTimer.reset();  
	} 
}

// 30 second timer for descent checking
Timer descendingTimer = Timer(0);
bool descentTimerStarted = false;

// The last altitude checked so we can figure out direction
double lastAltitude = 0;

// Checks to see if the payload has been descending for a minute 
bool isItDescending() {

	// Starting the timer
    if (data.gpsData.pos.alt <= lastAltitude && !descentTimerStarted) {

		descendingTimer = Timer(60000); // 1 minute
		lastAltitude = data.gpsData.pos.alt;
		descentTimerStarted = true;
		return false;

	}

	// Invalidating the timer if it is going up again
	if (data.gpsData.pos.alt > lastAltitude) {

		descentTimerStarted = false;
		lastAltitude = data.gpsData.pos.alt;
		return false;

	}

	// Returning true if the timer is done and we're still going down
	if (descendingTimer.isComplete() && descentTimerStarted && data.gpsData.pos.alt <= lastAltitude) {
		return true;
	}

	return false;

}

// Timer for the checking to see if the payload has landed or not
Timer landingTimer = Timer(120000);
double landingAltitude = 0;

// Checks to see if the altitude has stabilized +-50 meters for over 2 minutes
bool isLanded() {

	if ((data.gpsData.pos.alt  < landingAltitude + 25) && (data.gpsData.pos.alt  > landingAltitude - 25)) {
		if (landingTimer.isComplete()) {
			return true;
		}
	} else {
		landingTimer.reset();
		landingAltitude = data.gpsData.pos.alt;
	}
	return false;
}

// The 30 minute timer that allows the nitrogen sensor to configure
Timer initializationTimer = Timer(1800000);

// Timer to limit the number of times the payload checks the state
Timer stateTimer = Timer(10000);

void updateState() {

	if (!stateTimer.isComplete()) return;
	stateTimer.reset();

	switch (data.state) {
		case INITIALIZATION:
			if (initializationTimer.isComplete()) data.state = STANDBY;
			break;
		case STANDBY:
			if (data.gpsData.pos.alt > 500) data.state = PASSIVE;
			break;
		case PASSIVE:
			if (isItDescending()) data.state = DESCENT;
			break;
		case DESCENT:
			if (isLanded()) data.state = LANDED;
			break;
	}
}

// TODO Someone other than Sam W look over the error stuff to make sure it makes sense
// Timer for blinking error codes
Timer errorTimer = Timer(500);

// Displays the error through the LEDs
void displayErrors() {

	/****************************************** Error Definitions ******************************************
	 *
	 *	If all lights are off, then there were no errors.
	 *  If the ONLY LIGHT ON is the pico light, then GPS has gained lock
	 *
	 *	If all three lights are on, then there was an SD error
	 *	If the pico light and ONLY ONE error light is on, then there was a GPS error
	 *	If the only light on is ONE error light, then there was a BMP error
	 *  If both error lights are on and the pico light is off, then there was an NO2 error
	 *	If ONE error light is blinking and the other two are off, then there was a humidity sensor error
	 * 	If both error lights are blinking in sync, then there was a oxygen sensor error
	 *
	*******************************************************************************************************/

	// We don't care after it is ascending
	if (data.state != INITIALIZATION && data.state != STANDBY) return;

	switch(data.error){		
		case SD_ERROR:
			digitalWrite(config.pins.tiny, HIGH);
			digitalWrite(config.pins.smol, HIGH);
			digitalWrite(LED_BUILTIN, HIGH);
			break;

		case GPS_ERROR: 
			digitalWrite(config.pins.tiny, HIGH);
			digitalWrite(config.pins.smol, LOW);
			digitalWrite(LED_BUILTIN, HIGH);
			break;

		case BMP_ERROR:
			digitalWrite(config.pins.tiny, LOW);
			digitalWrite(config.pins.smol, HIGH);
			digitalWrite(LED_BUILTIN, LOW);
			break;

		case NO2_ERROR:
			digitalWrite(config.pins.tiny, HIGH);
			digitalWrite(config.pins.smol, HIGH);
			digitalWrite(LED_BUILTIN, LOW);
			break;

		case HUMID_ERROR: 
			digitalWrite(config.pins.tiny, LOW);
			digitalWrite(LED_BUILTIN, LOW);
			if (errorTimer.isComplete()) {
				digitalWrite(config.pins.smol, !digitalRead(config.pins.smol));
				errorTimer.reset();
			}
			break;

		case O2_ERROR:
			digitalWrite(LED_BUILTIN, LOW);
			if (errorTimer.isComplete()) {
				digitalWrite(config.pins.smol, !digitalRead(config.pins.smol));
				digitalWrite(config.pins.tiny, !digitalRead(config.pins.smol));
				errorTimer.reset();
			}
			break;

		case NO_ERROR:
			digitalWrite(config.pins.tiny, LOW);
			digitalWrite(config.pins.smol, LOW);
			if (data.gpsData.SIV > 3) {
				digitalWrite(LED_BUILTIN, HIGH);
			} else {
				digitalWrite(LED_BUILTIN, LOW);
			}
			break;

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


void collectData() {
	gps.updateData();
	bmp.updateData();
	humidity.updateData();
	no2.updateData();
	oxygen.updateData();
	data.missionTime = millis() / 1000.00;
	displayErrors();
}
