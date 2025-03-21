
#pragma once


class N02Sensor {
private:
    int WE1Pin;
    int Aux1Pin;
    int PTPin;

    float WEOffset;
    float AuxOffset;
    float sensitivity;
    float tempMult;

    // The analog to digital converter
    ADS1115_WE adc;

    // Internal function to read the channels
    float readChannel(ADS1115_MUX channel);

public:

    // Sets the pins and creates a new object
    NO2Sensor(int WE1, int Aux, int PT);

    // Initializes the sensor and adds the constants
    void init(float WEOffset, float AuxOffset, float sensitivity, float tempMult);

    // Returns the NO2 concentration in ppb

}
