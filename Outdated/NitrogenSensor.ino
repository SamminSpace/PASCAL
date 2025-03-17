#include<ADS1115_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48
ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

float WE;
float Aux;

float Volt_PT;
int WE1Pin = 34;
int Aux1Pin = 32;
int PTPin = 31;

// formulas
float Temp_PT;        // PT1000
float WE_Real;    // NO2 WE
float Aux_Real;   // NO2 Aux
float NO2;            // NO2 ppb

//Calibration Constants
// for SN1 or NO2 
float WE_offset = 225;
float Aux_offset = 224;
float SENSITIVITY = 0.225; //in mV/ppb
// Will not be a constant
int nT = 1.3; //temperature dependent multiplier

void setup ()
{
  Serial.begin (9600);
  Wire.begin();
  if(!adc.init()){
    Serial.println("ADS1115 not connected!");
  }

  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setCompareChannels(ADS1115_COMP_0_GND);
  adc.setMeasureMode(ADS1115_CONTINUOUS); 

  Serial.println("ADS1115 Example Sketch - Continuous Mode");
  Serial.println("All values in volts");
  Serial.println();
}

void loop()
{
  float voltage = 0.0;

  Serial.println(" ");
  Serial.print("Worker: ");
  adc.setCompareChannels(ADS1115_COMP_0_1);
  WE = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  Serial.print(WE);
  
  Serial.print(",   Aux: ");
  adc.setCompareChannels(ADS1115_COMP_2_3);
  Aux = adc.getResult_mV(); 
  Serial.print(Aux);
  Serial.print(" ");

  /*Serial.print(",   2: ");
  adc.setCompareChannels(ADS1115_COMP_2_GND);
  Volt_PT = adc.getResult_mV();
  Serial.print(Volt_PT);

  Serial.print(",   3: ");
  adc.setCompareChannels(ADS1115_COMP_3_GND);
  voltage = adc.getResult_mV();
  Serial.println(voltage); */

  WE_Real = WE - WE_offset;   //these are in mV
  Aux_Real = nT * (Aux - Aux_offset);  //in mV
  NO2 = (WE_Real - Aux_Real)/(SENSITIVITY);
  Serial.print("Corrected WE = ");
  Serial.print(WE_Real);
  Serial.print(" mV, ");
  Serial.print(" Corrected Aux = ");
  Serial.print(Aux_Real);
  Serial.print(" mV, ");
  Serial.print(" - NO2 CONCENTRATION = ");
  Serial.print(NO2);
  Serial.print(" ppb");
  Serial.println(" ");

 delay(1000); 

}  

float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  return voltage;
}
