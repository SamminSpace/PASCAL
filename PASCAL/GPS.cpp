// #include <SparkFun_u-blox_GNSS_v3.h> //http://librarymanager/All#SparkFun_u-blox_GNSS_v3
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 

#include "Time.h"
#include "GPS.h"
#include "Config.h"


errorState GPS::init() {
  Serial.println("Beginning init function for GPS");
    // Optional debug statements are commented out

  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();

    // Initialization
    if (!gps.begin()) {
      Serial.println("GPS ERROR");
      return GPS_ERROR;
    }

    // Updating settings
    gps.setI2COutput(COM_TYPE_UBX);
    gps.setNavigationFrequency(5);
    if (gps.setDynamicModel(DYN_MODEL_AIRBORNE4g) == false) {
        // TODO Error codes
    }
    gps.saveConfiguration();

    if (gps.getSIV() < 3) {
        Serial.println("Waiting for lock, SIV: "); Serial.println(gps.getSIV());
        
    }

  return NO_ERROR;
}

void GPS::update() {

  // Checking for new data
  //gps.checkUblox();
  // if (gps.getPVT() == false) {
  //     //Serial.println("Nothing new");
  //     return;  
  // }
  siv = gps.getSIV();
  altitude = gps.getAltitude() / 1000.0;
  longitude = (gps.getLongitude()) * pow(10, -7);
  latitude = (gps.getLatitude()) * pow(10, -7);
  time.year = (int)gps.getYear();
  time.month = (int)gps.getMonth();
  time.day = (int)gps.getDay();
  time.hour = (int)gps.getHour();
  time.minute = (int)gps.getMinute();
  time.second = (int)gps.getSecond();
  
  tick.reset();
}

float GPS::getAltitude() {
  if (tick.isComplete()) {
    update();
  }
  return altitude;
}

float GPS::getLongitude() {
  if (tick.isComplete()) {
    update();
  }
    return longitude;
}

float GPS::getLatitude() {
  if (tick.isComplete()) {
    update();
  }
    return latitude;
}

UTCTime GPS::getUTCTime() {
  if (tick.isComplete()) {
    update();
  }
  return time;
}

int GPS::getSIV() {
  if (tick.isComplete()) {
    update();
  }
    return siv;
}
