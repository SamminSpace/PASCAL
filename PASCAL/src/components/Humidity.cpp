
#include <Adafruit_HDC302x.h>
#include "components/Humidity.h"
#include "PASCAL.h"

void HumiditySensor::turnOn() {
    if(!humidity.begin()){
		data.error = data.error > HUMID_ERROR ? data.error : HUMID_ERROR;	
    }
}

void HumiditySensor::updateData() {
	// TODO Update this to be faster
	double humid;
	double temp;
  	humidity.readTemperatureHumidityOnDemand(temp, humid, TRIGGERMODE_LP0);
	data.atmoData.humidity = humid;
	data.atmoData.humiditySensorTemperature = temp;
}
