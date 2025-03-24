
#include <Adafruit_HDC302x.h>
#include "Config.h"
#include "Humidity.h"


errorState HumiditySensor::init() {
    if(!humidity.begin()){
        return HUMID_ERROR;
    }
    return NO_ERROR;
}

float HumiditySensor::getWetness() {
    return humidity.readTemperatureHumidityOnDemand(temp, RH, TRIGGERMODE_LP0);


}
