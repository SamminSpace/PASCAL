#ifndef HUMIDITY_H
#define HUMIDITY_H
#include "Config.h"


class HumiditySensor {
private:

    Adafruit_HDC302x humidity; //IDK IF RIGHT

    double temp; //temperature dont by humidity
    double RH; // humdity 

public:

    // Initializes the humid sensor
    errorState init();

    // Reads from the humid sensor
    float getWetness();

};
#endif
