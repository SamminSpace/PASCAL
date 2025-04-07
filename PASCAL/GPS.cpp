// #include <SparkFun_u-blox_GNSS_v3.h> //http://librarymanager/All#SparkFun_u-blox_GNSS_v3
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 

#include "Time.h"
#include "GPS.h"
#include "Config.h"

// Global stuff so that we can pass in a non-class variable
double lastLongitude;
double lastAltitude;
double lastLatitude;
UTCTime mostRecentTime;
int mostRecentSIV;


// Function for callback so that we can make it update really quickly
void pvtCallback(UBX_NAV_PVT_data_t *ubxDataStruct) {
    lastAltitude = ubxDataStruct->height / 1000.0;
    lastLatitude = ((double)ubxDataStruct->lat) * pow(10, -7);
    lastLongitude = ((double)ubxDataStruct->lon) * pow(10, -7);
  
    mostRecentTime = {
        (int)ubxDataStruct->year,
        (int)ubxDataStruct->month,
        (int)ubxDataStruct->day,
        (int)ubxDataStruct->hour,
        (int)ubxDataStruct->min,
        (int)ubxDataStruct->sec,
    };
    mostRecentSIV = ubxDataStruct->numSV;
}


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
    gps.setAutoPVTcallbackPtr(&pvtCallback);

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

// Fetches data if there is any 
void GPS::prefetchData() {
    gps.checkUblox();
    gps.checkCallbacks();
    altitude = lastAltitude;
    longitude = lastLongitude;
    latitude = lastLatitude;
    time = mostRecentTime;
    siv = mostRecentSIV;
    tick.reset();
}

float GPS::getAltitude() {
  if (tick.isComplete()) {
    prefetchData();
  }
  return altitude;
}

float GPS::getLongitude() {
  if (tick.isComplete()) {
    prefetchData();
  }
    return longitude;
}

float GPS::getLatitude() {
  if (tick.isComplete()) {
    prefetchData();
  }
    return latitude;
}

UTCTime GPS::getUTCTime() {
  if (tick.isComplete()) {
    prefetchData();
  }
  return time;
}

int GPS::getSIV() {
  if (tick.isComplete()) {
    update();
  }
    return siv;
}
