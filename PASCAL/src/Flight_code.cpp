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

void setup() {
	initPins();
	initComponents();
	initLEDs(3000);
}

void loop() {
	blinky(); 
	collectData();
	logger.writeTelemetry();
	updateState();
	if (data.state == PASSIVE) controller.sampling();
}











