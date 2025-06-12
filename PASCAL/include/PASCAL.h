#pragma once

#include <Arduino.h>
#include "Config.h"
#include "Data.h"
#include "components/Logger.h"
#include "components/GPS.h"
#include "components/PumpController.h"



// Allowing these to be accessed in other files
extern Config config;
extern Data data;
extern Logger logger;
extern GPS gps;
extern PumpController controller;


void initPins();
void logData();
void collectData();