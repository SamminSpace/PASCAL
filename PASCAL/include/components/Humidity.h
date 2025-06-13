#pragma once

#include "Config.h"
#include <Adafruit_HDC302x.h>

class HumiditySensor {
private:

    Adafruit_HDC302x humidity; 

public:

    // Initializes the humid sensor
    void turnOn();

	// Updates the data we have from the sensor
	void updateData();

};

