#ifndef BMP_H
#define BMP_H
#include <Adafruit_BMP3XX.h>

#include "Config.h"

class BMP {


public:
    Adafruit_BMP3XX bmp;

    // Initializes the BMP 
    errorState init();

    // Reads from the BMP and the reading
    double getAltitude(float seaLevelPressure);
    double getPressure(float seaLevelPressure);
    double getTemperature(float seaLevelPressure);

};
#endif
