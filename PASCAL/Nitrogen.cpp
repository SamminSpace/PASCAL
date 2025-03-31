

#include "Nitrogen.h"
#include "Config.h"

float NO2Sensor::readChannel(ADS1115_MUX channel) {

  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  return voltage;

}

NO2Sensor::NO2Sensor(int WE1, int Aux, int PT) {
    WE1Pin = WE1;
    Aux1Pin = Aux;
    PTPin = PT;
    adc = ADS1115_WE(0x48);
}

errorState NO2Sensor::init(float WEOffset, float AuxOffset, float sensitivity, float tempMult) {

    this->WEOffset = WEOffset;
    this->AuxOffset = AuxOffset;
    this->sensitivity = sensitivity;
    this->tempMult = tempMult;

    if(!adc.init()){
       return NO2_ERROR;
    }

    adc.setVoltageRange_mV(ADS1115_RANGE_6144);
    adc.setCompareChannels(ADS1115_COMP_0_GND);
    adc.setMeasureMode(ADS1115_CONTINUOUS); 

    return NO_ERROR;
}

float NO2Sensor::getNO2() {
    adc.setCompareChannels(ADS1115_COMP_0_1);
    float WE = adc.getResult_mV(); // alternative: getResult_mV for Millivolt

    adc.setCompareChannels(ADS1115_COMP_2_3);
    float Aux = adc.getResult_mV(); 

    float WE_Real = WE - WEOffset;   //these are in mV
    float Aux_Real = tempMult * (Aux - AuxOffset);  //in mV
    return (WE_Real - Aux_Real)/(sensitivity);
}


