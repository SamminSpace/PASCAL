#include <Wire.h>
#include <Adafruit_BMP3XX.h>
#include "DFRobot_OxygenSensor.h"

// Define custom I2C pins
#define SDA_PIN 12  // Change to your desired SDA pin
#define SCL_PIN 13  // Change to your desired SCL pin

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP3XX bmp;  // Create BMP390 object


#define Oxygen_IICAddress ADDRESS_3
#define COLLECT_NUMBER  10             // collect number, the collection range is 1-100.
DFRobot_OxygenSensor oxygen;

void setup() {
    Serial.begin(9600);
    delay(1000);
    
    // Set up I2C on custom pins
    Wire.setSDA(SDA_PIN);
    Wire.setSCL(SCL_PIN);
    Wire.begin();  // Start I2C communication

    // Initialize BMP390
    while (!bmp.begin_I2C()) {
        Serial.println("Could not find a valid BMP390 sensor, check wiring!");
        delay(1000);
    }


    Serial.begin(9600);
    while(!oxygen.begin(Oxygen_IICAddress)){
      Serial.println("I2c device number error !");
     delay(1000);
   }
    
    Serial.println("I2c connect success to all devices!");
   
}

void loop() {

  ReadBMP();
  OxygenDetect();

  Serial.println();
  delay(1000);
}

void ReadBMP(){
  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
}


void OxygenDetect(){
  float oxygenData = oxygen.getOxygenData(COLLECT_NUMBER);
  Serial.print("Oxygen concentration is ");
  Serial.print(oxygenData);
  Serial.println(" %vol");
}
