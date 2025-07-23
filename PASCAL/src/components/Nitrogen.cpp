

#include "components/Nitrogen.h"
#include "PASCAL.h"


float NO2Sensor::readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  return voltage;
}

NO2Sensor::NO2Sensor() {
    adc = ADS1115_WE(0x48);
}

void NO2Sensor::init(float WEOffset, float AuxOffset, float sensitivity, float tempMult) {
    this->WEOffset = WEOffset;
    this->AuxOffset = AuxOffset;
    this->sensitivity = sensitivity;
    this->tempMult = tempMult;

    if(!adc.init()){
       data.error = data.error > NO2_ERROR ? data.error : NO2_ERROR;	
       logger.writeError("ADC Initialization Error");
    }

    adc.setVoltageRange_mV(ADS1115_RANGE_6144);
    adc.setCompareChannels(ADS1115_COMP_0_GND);
    adc.setMeasureMode(ADS1115_CONTINUOUS); 
}

void NO2Sensor::updateData() {
    adc.setCompareChannels(ADS1115_COMP_0_1);
    float WE = adc.getResult_mV(); // alternative: getResult_mV for Millivolt

    adc.setCompareChannels(ADS1115_COMP_2_3);
    float Aux = adc.getResult_mV(); 

    data.WE_real = WE - WEOffset;   // mV
    data.Aux_real = tempMult * (Aux - AuxOffset);  // mV
    data.atmoData.no2 = (data.WE_real - data.Aux_real)/(sensitivity);
}


