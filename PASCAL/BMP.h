#pragma once
#include <Adafruit_BMP3XX.h>


class BMP {
private:
    Adafruit_BMP3XX bmp;

public:

    // Initializes the BMP 
    void init();

    // Reads from the BMP and returns an array of the readings:
    // [temperature, pressure, altitude] (*C, hPa, m)
    double* readBMP(float seaLevelPressure);

};

