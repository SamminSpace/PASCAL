
#pragma once
#include <ADS1115_WE.h> 
#include "Data.h"
#include "Config.h"

class NO2Sensor {
private:

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
    NO2Sensor();

    // Initializes the sensor and adds the constants
    void init(float WEOffset, float AuxOffset, float sensitivity, float tempMult);

    // Updates the nitrogen reading in Data
    void updateData();
	

};
