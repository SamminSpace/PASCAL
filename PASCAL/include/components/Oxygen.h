#ifndef OXYGEN_H
#define OXYGEN_H
#include "DFRobot_OxygenSensor.h"
#include "Config.h"

class OxygenSensor {
private:

    DFRobot_OxygenSensor oxygen;

	// Lower is faster, but less precise (We are recording every single sample, so maybe lower is better)
    int collectionNumber = 10; // Can be from 1-100

public:

    // Initializes the oxygen sensor
    void init();

    // Reads from the oxygen sensor
    void updateData();

};

#endif

