
#include <Adafruit_HDC302x.h>



void HumiditySensor::init() {
    if(!humidity.begin()){
        error = HUMID_ERROR;
    }
}

float HumiditySensor::getWetness() {
    return hdc.readTemperatureHumidityOnDemand(temp, RH, TRIGGERMODE_LP0);


}
