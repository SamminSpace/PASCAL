#ifndef HUMIDITY_H
#define HUMIDITY_H
#include "Config.h"
#include <Adafruit_HDC302x.h>

class HumiditySensor {
private:

    Adafruit_HDC302x humidity; //IDK IF RIGHT

    double temp; //temperature dont by humidity
    double RH; // humdity 

    // Updates the data we have from the sensor
    void update();

public:

    // Initializes the humid sensor
    errorState turnOn();

    // Reads from the humid sensor
    float getWetness();

    // Reads the temperature from the sensor
    float getHotness();

};
#endif
