
#include <Adafruit_HDC302x.h>
#include "Config.h"
#include "Humidity.h"


errorState HumiditySensor::turnOn() {
    if(!humidity.begin()){
        return HUMID_ERROR;
    }
    return NO_ERROR;
}

void HumiditySensor::update() {
  humidity.readTemperatureHumidityOnDemand(temp, RH, TRIGGERMODE_LP0);
}

float HumiditySensor::getWetness() {
    update();
    return RH; 
}

float HumiditySensor::getHotness() {
    update();
    return temp; 
}
