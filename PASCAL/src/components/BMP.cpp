
#include "components/BMP.h"
#include "PASCAL.h"


void BMP::updateTemperature(){
    bmp.readAltitude(config.seaLevelPressure);
    data.atmoData.temperature = bmp.temperature;
}
void BMP::updatePressure(){
    bmp.readAltitude(config.seaLevelPressure);
    data.atmoData.pressure = bmp.pressure / 100.0;
}
void BMP::updateAltitude(){
   data.atmoData.alt = bmp.readAltitude(config.seaLevelPressure);
}

void BMP::updateData() {
    // TODO update this to be faster
    data.atmoData.alt = bmp.readAltitude(config.seaLevelPressure);	
    data.atmoData.pressure = bmp.pressure / 100.0;
    data.atmoData.temperature = bmp.temperature;
}


void BMP::init() {
    if (!bmp.begin_I2C()) {
        data.error = data.error > BMP_ERROR ? data.error : BMP_ERROR;	
        logger.writeError("BMP Initialization Error");        
    }
}
