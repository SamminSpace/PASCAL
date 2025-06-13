#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 
#include "DFRobot_OxygenSensor.h"
#include "Data.h"
#include "Config.h"
#include "PASCAL.h"
#include "components/Logger.h"
#include "components/BMP.h"
#include "components/Oxygen.h"
#include "components/GPS.h"
#include "components/Humidity.h"
#include "components/PumpController.h"

void fakeAltitude();

void setup() {
	Serial.begin(9600);
	initPins();
	initComponents();
	initLEDs(5000);

	// Delay to allow the serial monitor to open
	delay(5000);

	// Skipping the configuration time
	data.state = STANDBY;
}

void loop() {
	blinky(); 
	collectData();
	fakeAltitude();
	logger.writeTelemetry();
	updateState();
	if (data.state == PASSIVE) controller.sampling();
	// Printing the altitude and the state
	Serial.println("Altitude: " + String(data.gpsData.pos.alt) + "\tState: " + getFlightStateString(data.state) + "\tSampling State: " + getSampleStateString(data.sampleState));
}


// Changes the altitude so we can simulate the flight
// 	 I REJECT YOUR REALITY AND SUBSTITUTE MY OWN
// 30 seconds to get to 600 meters
// ~5 minutes in passive flight
// 2 minute in descent (PASCAL be speedy)
int direction = 1;
double lastFakeAltitude = 0;
Timer altTimer = Timer(1000);
void fakeAltitude() {

	if (!altTimer.isComplete()) {
		data.gpsData.pos.alt = lastFakeAltitude;
		return;
	} 

	if (direction == 1) {
		if (lastFakeAltitude < 600) {
			lastFakeAltitude += 20;
		} else {
			lastFakeAltitude += 49;
		} 
	} else {
		if (lastFakeAltitude > 0) {
			lastFakeAltitude -= 250;
		} else if (lastFakeAltitude < 0) {
			lastFakeAltitude = 0;
		}
	}

	// Burst altitude 
	if (lastFakeAltitude > 16000) {
		direction = -1;
	}

	data.gpsData.pos.alt = lastFakeAltitude;

	altTimer.reset();

}










