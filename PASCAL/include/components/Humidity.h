#ifndef HUMIDITY_H
#define HUMIDITY_H
#include "Config.h"
#include <Adafruit_HDC302x.h>

class HumiditySensor {
private:

    Adafruit_HDC302x humidity; 

    double temp; //temperature measured from the humidity sensor cached if needed for whatever reason

public:

    // Initializes the humid sensor
    void turnOn();

	// Updates the data we have from the sensor
	void update();

    // Reads the temperature from the humidity sensor
    float getHotness();

};
#endif
