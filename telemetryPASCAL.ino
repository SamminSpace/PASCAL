//telemrtey?
#include <SD.h>


//data being collected
unsigned long missionTime;
String payloadState; //is needed?
String payload = "PASCAL"; //needed?
int packetNumber = 0; //needed?

float nitrogen;
float oxyclean;
float humidity; //should be doing

float altitude;
float temperature;
float pressure;

float gyroX;
float gyroY;
float gyroZ;
float accelX;
float accelY;
float accelZ;
float magX;
float magY;
float magZ;

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
    "UTC Time, Nitrogen Concentration, Oxygen Concentration, Humidity, Altitude, "
    "Temperature, Pressure, Gyro X, Gyro Y, Gyro Z, Acceleration X, Acceleration Y, "
    "Accerlaerion Z, Magnetometer X, Magnetometer Y, Magnetometer Z, GPS Altitude, "
    "GPS Laitiude, GPS Longitude");
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
    "," + missionTime + "," + UTC + "," + nitrogen + "," + oxyclean + "," 
    + humidity + "," + altitude + "," + temperature + "," + pressure +
    gyroX + "," + gyroY + "," + gyroZ + "," + accelX + "," + accelY + 
    accelZ + "," + magX + "," + magY + "," + magZ + "," + gpsAlt + ","
    + gpsLat + "," + gpsLong);
    dataFile.close();

    Serial.println("Sucessful log");
  }

  packetNumber ++; 
}
