#ifndef BMP_H
#define BMP_H
#include <Adafruit_BMP3XX.h>

#include "Config.h"

class BMP {
private:
    Adafruit_BMP3XX bmp;

public:

    // Initializes the BMP 
    errorState init();

    // Reads from the BMP and the reading
    double getAltitude(float seaLevelPressure);
    double getPressure();
    double getTemperature();

};
#endif
