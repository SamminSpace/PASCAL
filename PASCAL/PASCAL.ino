

// This is what Arduino IDE will actually be running
// Everything else will be imported

// Library imports
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 
#include "DFRobot_OxygenSensor.h"

// Sensor imports
#include "Logger.h"
#include "BMP.h"
#include "Oxygen.h"
#include "GPS.h"
#include "Config.h"
#include "Humidity.h"


// Declaring all of the sensors and things
Config config;  
GPS gps; 
HumiditySensor humidity;
BMP bmp;
OxygenSensor oxygen;
Logger sd = Logger((String("Testing")));  //probelms in config idk why

//Error Code Stuff
errorState error;
unsigned long beginMillis;
int period = 500;
void Blinky() {
  unsigned long currentMillis;
  
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - beginMillis >= period)  //test whether the period has elapsed
  {
    digitalWrite(config.pins.blinker, !digitalRead(config.pins.blinker));  //if so, change the state of the LED.  Uses a neat trick to change the state
    beginMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  } 
}


void setup() {

  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();

    // TODO finish the flight portion

    // Setting up the chipselect
    // pinMode(config.pins.chipSelect, OUTPUT);
    Serial.begin(9600);
    while (!Serial);

    // Initializing the things
    gps.init();
    humidity.turnOn();
    bmp.init();
    oxygen.init();
    sd.init(config.pins.chipSelect);

    pinMode(LED_BUILTIN, OUTPUT);

    switch(error){		//error 1 will be SD (all on)
    case SD_ERROR:
    digitalWrite(config.pins.tiny, HIGH);
    digitalWrite(config.pins.smol, HIGH);
    break;
    
    case GPS_ERROR:  //error 2 is GPS (1 on/off)
    sd.write("Hey, your GPS is messed up!");
    digitalWrite(config.pins.tiny, HIGH);
    digitalWrite(config.pins.smol, LOW);
    break;
    
    case BMP_ERROR:   //BMP (other on/off)
    sd.write("BMP not found.");
    digitalWrite(config.pins.tiny, LOW);
    digitalWrite(config.pins.smol, HIGH);
    break;
    
   case NO2_ERROR:  // NO2 (tiny blinks and smol on)
    sd.write("NO2 (the problem child) is not functioning");
    digitalWrite(config.pins.smol, HIGH);
    config.pins.blinker = config.pins.tiny;
    Blinky();
    break;
    
    case HUMID_ERROR:  //Humidity (smol blinks and tiny on)
    sd.write("Must be too dry bc humidty not detected.");
    digitalWrite(config.pins.tiny, HIGH);
    config.pins.blinker = config.pins.smol;
    Blinky();
    break;
     
    case O2_ERROR:   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
    sd.write("Apparently no oxygen found so idk how you are alive rn");
    digitalWrite(config.pins.tiny, LOW);
    config.pins.blinker = config.pins.smol;
    Blinky();
    break;
      
    default:
    sd.write("lets go!");
    digitalWrite(config.pins.tiny, LOW);
    digitalWrite(config.pins.smol, LOW);
  }

  // missing: nitrogen, WE, Aux, BMP Alt
  sd.write("Payload, Payload State, Packet Number, Mission Time, SIV, "
    "UTC Time, Oxygen Concentration, Other Temp, Humidity, "
    "Temperature, Pressure, GPS Altitude, GPS Laitiude, GPS Longitude");


}

void loop() {

  /* I am very well aware that these are not needed 
  ` but if someone wanted to run individual sensors
    they are all here! See? I'm so smart
  */

  // bmp.getAltitude();
  bmp.getPressure();
  bmp.getTemperature();

  gps.getSIV();
  gps.getAltitude();
  gps.getLatitude();
  gps.getLongitude();
  gps.getUTCTime();

  oxygen.getOxygen();

  humidity.getHotness();
  humidity.getWetness();
 
  // First of all, testing the SD logging
  sd.write("Pick a sesnor");
  Serial.write("Printing out whatevere");

  digitalWrite(LED_BUILTIN, HIGH);

}

// woah a function that actually puts all the data in a massive string
void logData (){ //future reference: nitrogen, Aux, WE
  config.missionTime = millis();

  String Data = config.payload + ", " + 
  "PAYLOAD STATE" + ", " + 
  String(config.packetNumber) + ", " + 
  String(config.missionTime) + ", " + 
  String(gps.getSIV()) + ", " + 
  "GPS TIME" + ", " + 
  String(oxygen.getOxygen()) + ", " + 
  String(humidity.getHotness()) + ", " + 
  String(humidity.getWetness()) + ", " + 
  String(bmp.getTemperature()) + ", " + 
  String(bmp.getPressure()) + ", " + 
  String(gps.getAltitude()); + ", " + 
  String(gps.getLatitude()) + ", " + 
  String(gps.getLongitude());
  
  sd.write(Data);

  config.packetNumber ++;
}
