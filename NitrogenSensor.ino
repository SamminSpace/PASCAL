int SN1_WE;
int SN1_Aux;

int Volt_PT;
int WE1Pin = 2;
int Aux1Pin = 3;
int PTPin = 1;

// formulas
float Temp_PT;        // PT1000
float SN1_WE_Real;    // NO2 WE
float SN1_Aux_Real;   // NO2 Aux
float NO2;            // NO2 ppb

//Calibration Constants
// for SN1 or NO2 
float SN1_TOTAL_WE = 0.1720;
float SN1_TOTAL_AE = 0.2240;
float SN1_SENSITIVITY = 0.2080;

void setup ()
{
  Serial.begin (9600);
}

void loop()
{
  SN1_WE = analogRead(WE1Pin);
  delay(10);
  SN1_Aux = analogRead(Aux1Pin);
  delay(10);
  Volt_PT = analogRead(PTPin);
  
  Temp_PT = 20 + ((Volt_PT - (0.297)*(0.3000))/(0.0010));
  Serial.print("Temperature = ");
  Serial.print(Temp_PT);
  Serial.println();
  
  if(Temp_PT <= 10)
  {
    SN1_WE_Real = SN1_WE - SN1_TOTAL_WE;
    SN1_Aux_Real = 1.090*(SN1_Aux - SN1_TOTAL_AE);
    NO2 = (SN1_WE_Real - SN1_Aux_Real)/(SN1_SENSITIVITY);
    Serial.print("NO2 Voltage = ");
    Serial.print(SN1_WE);
    Serial.print(" V");
    Serial.print(" ");
    Serial.print(SN1_Aux);
    Serial.print(" V");
    Serial.print(" - NO2 CONCENTRATION = ");
    Serial.print(NO2);
    Serial.print(" ppb");
    Serial.println();
  }
  
  if(Temp_PT >= 30)
  {
    SN1_WE_Real = SN1_WE - SN1_TOTAL_WE;
    SN1_Aux_Real = 3.000*(SN1_Aux - SN1_TOTAL_AE);
    NO2 = (SN1_WE_Real - SN1_Aux_Real)/(SN1_SENSITIVITY);
    Serial.print("NO2 Voltage = ");
    Serial.print(SN1_WE);
    Serial.print(" V");
    Serial.print(" ");
    Serial.print(SN1_Aux);
    Serial.print(" V");
    Serial.print(" - NO2 CONCENTRATION = ");
    Serial.print(NO2);
    Serial.print(" ppb");
    Serial.println();
  
  }
  
  else
  {
    SN1_WE_Real = SN1_WE - SN1_TOTAL_WE;
    SN1_Aux_Real = 1.3500*(SN1_Aux - SN1_TOTAL_AE);
    NO2 = (SN1_WE_Real - SN1_Aux_Real)/(SN1_SENSITIVITY);
    Serial.print("NO2 Voltage = ");
    Serial.print(SN1_WE);
    Serial.print(" V");
    Serial.print(" ");
    Serial.print(SN1_Aux);
    Serial.print(" V");
    Serial.print(" - NO2 CONCENTRATION = ");
    Serial.print(NO2);
    Serial.print(" ppb");
    Serial.println();
  }

}  