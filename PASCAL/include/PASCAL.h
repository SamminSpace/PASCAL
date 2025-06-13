#pragma once

#include <Arduino.h>
#include "Config.h"
#include "Data.h"
#include "components/Logger.h"
#include "components/GPS.h"
#include "components/PumpController.h"
#include "components/Humidity.h"
#include "components/BMP.h"
#include "components/Oxygen.h"
#include "components/Nitrogen.h"



// Allowing these to be accessed in other files
extern Config config;
extern Data data;
extern Logger logger;
extern GPS gps;
extern PumpController controller;
extern HumiditySensor humidity;
extern BMP bmp;
extern OxygenSensor oxygen;
extern NO2Sensor no2;


void initPins();
void logData();
void initComponents();
void displayErrors();
void collectData();
void initLEDs(int msDelay);
void blinky();
bool isItDescending();
bool isLanded();
void updateState();
String getFlightStateString(FlightState state);
String getSampleStateString(SampleState state);
String getErrorString(Error error);