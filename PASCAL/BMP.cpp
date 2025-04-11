
#include "BMP.h"
#include "Config.h"

//! Looks like we can make this faster too, just like the HAVOC BME, check here https://github.com/adafruit/Adafruit_BMP3XX/blob/master/Adafruit_BMP3XX.cpp
// It sets it into sleep mode immediately after measuring, if we change that we should be able to get it to continually measure

double BMP::getTemperature(float seaLevelPressure){
  bmp.readAltitude(seaLevelPressure);
  return bmp.temperature;
}
double BMP::getPressure(float seaLevelPressure){
  bmp.readAltitude(seaLevelPressure);
  return bmp.pressure / 100.0;
}
double BMP::getAltitude(float seaLevelPressure){
  return bmp.readAltitude(seaLevelPressure);
}


errorState BMP::init() {
    if (!bmp.begin_I2C()) {
        return BMP_ERROR;
    }
    return NO_ERROR;
}
