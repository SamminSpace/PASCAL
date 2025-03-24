
#include "BMP.h"


double* BMP::readBMP(float seaLevelPressure){
  return [bmp.temperature, bmp.pressure / 100.0,bmp.readAltitude(seaLevelPressure)];

}

void BMP::init() {
    if (!bmp.begin_I2C()) {
        error = BMP_ERROR;
    }
}
