
#include "Inlcude/BMP.h"


double[3] BMP::readBMP(float seaLevelPressure){
  return [bmp.temperature, bmp.pressure / 100.0,bmp.readAltitude(seaLevelPressure)];

}

void BMP::init() {
    while (!bmp.begin_I2C()) {
        Serial.println("Could not find a valid BMP390 sensor, check wiring!");
        delay(1000);
    }
}
