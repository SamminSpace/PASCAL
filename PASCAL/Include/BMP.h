#pragma once

class BMP {
private:
    Adafruit_BMP3XX bmp;

public:

    // Initializes the BMP 
    void init();

    // Reads from the BMP and returns an array of the readings:
    // [temperature, pressure, altitude] (*C, hPa, m)
    double[3] readBMP(float seaLevelPressure);

}

