#include <Adafruit_HDC302x.h>
#define SDA_PIN 12  
#define SCL_PIN 13

Adafruit_HDC302x hdc = Adafruit_HDC302x();

void setup() {
  
  Serial.begin(9600);
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);

  Serial.println("Adafruit HDC302x Simple Test");

  while (! hdc.begin(0x44, &Wire)) {
    Serial.println("Could not find sensor?");
    delay(1000);
  }
  
}

void loop() {
  double temp = 0.0;
  double RH = 0.0;

  hdc.readTemperatureHumidityOnDemand(temp, RH, TRIGGERMODE_LP0);

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(RH);
  Serial.println(" %");
  delay(2000);
  
}
