#ifndef OXYGEN_H
#define OXYGEN_H
#include "DFRobot_OxygenSensor.h"
#include "Config.h"

class OxygenSensor {
private:

    DFRobot_OxygenSensor oxygen;

    int collectionNumber = 10; // Can be from 1-100

public:

    // Initializes the oxygen sensor
    errorState init();

    // Reads from the oxygen sensor
    float getOxygen();

};

#endif

