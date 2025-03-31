//telemrtey?
#include <SD.h>
#include <Wire.h>


//data being collected
unsigned long missionTime;
String payloadState; 
String payload = "PASCAL"; 
int packetNumber = 0; 

float nitrogen;
float WE;
float Aux;
float oxyclean;
float humidity;

float altitude;
float temperature;
float pressure;

float gpsAlt;
float gpsLat;
float gpsLong;
String UTC; 

//set pins AND CHECK THEM 
const int _MISO = 4;
const int _MOSI = 7;
const int _CS = 5;
const int _SCK = 6;




void setup() {
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(_CS)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");

  //How make new file name each time code runs?
  File dataFile = SD.open("PASCAL.csv", FILE_WRITE);  

  //if file exists, then writes Header
  if (dataFile) {
    dataFile.println("Payload, Payload State, Packet Number Mission Time, "
    "UTC Time, Nitrogen Concentration, Raw WE, Raw Aux, Oxygen Concentration, Humidity, Altitude, "
    "Temperature, Pressure, GPS Altitude, GPS Laitiude, GPS Longitude");
    dataFile.close();
    Serial.println("Wrote header.");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}



void logSD(){
  missionTime = millis() / 1000; 

   File dataFile = SD.open("PASCAL.csv", FILE_WRITE);  

  if (dataFile) {
    dataFile.println(payload + "," + payloadState + "," + packetNumber + 
    "," + missionTime + "," + UTC + "," + nitrogen + "," + WE + "," + Aux + "," + oxyclean + "," 
    + humidity + "," + altitude + "," + temperature + "," + pressure +
    gpsAlt + "," + gpsLat + "," + gpsLong);
    dataFile.close();

    Serial.println("Sucessful log");
  }

  packetNumber ++; 
}
