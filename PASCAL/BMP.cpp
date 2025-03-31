
#include "BMP.h"
#include "Config.h"


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
