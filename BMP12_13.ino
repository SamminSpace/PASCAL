#include <Wire.h>
#include <Adafruit_BMP3XX.h>

// Define custom I2C pins
#define SDA_PIN 12  // Change to your desired SDA pin
#define SCL_PIN 13  // Change to your desired SCL pin

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP3XX bmp;  // Create BMP390 object

void setup() {
    Serial.begin(115200);
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

    Serial.println("BMP390 Sensor Found!");
}

void loop() {
    if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    delay(500);
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}
