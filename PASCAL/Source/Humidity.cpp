
#include <Adafruit_HDC302x.h>



void HumiditySensor::init() {
    if(!humidity.begin()){
        delay(1000);
        // TODO error codes
    }
}

float humiditySensor::getWetness() {
    return hdc.readTemperatureHumidityOnDemand(temp, RH, TRIGGERMODE_LP0);


}
