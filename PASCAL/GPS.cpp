// #include <SparkFun_u-blox_GNSS_v3.h> //http://librarymanager/All#SparkFun_u-blox_GNSS_v3
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 

#include "Time.h"
#include "GPS.h"
#include "Config.h"


errorState GPS::init() {
    // Optional debug statements are commented out

    // Initialization
    if (!gps.begin()) {
      return GPS_ERROR;
    }

    // Updating settings
    gps.setI2COutput(COM_TYPE_UBX);
    gps.setNavigationFrequency(5);
    if (gps.setDynamicModel(DYN_MODEL_AIRBORNE4g) == false) {
        // TODO Error codes
    }
    gps.saveConfiguration();

    while (gps.getSIV() < 3) {
        // error = SD_ERROR;
        // TODO Error codes
        //Do we want error if no lock? 
    }

  return NO_ERROR;
}

double GPS::getAltitude() {
    return gps.getAltitude() / 1000.0;
}

double GPS::getLongitude() {
    return ((double)gps.getLongitude()) * pow(10, -7);
}

double GPS::getLatitude() {
    return ((double)gps.getLatitude()) * pow(10, -7);
}

UTCTime GPS::getUTCTime() {
    UTCTime toReturn;
    toReturn.year = (int)gps.getYear();
    toReturn.month = (int)gps.getMonth();
    toReturn.day = (int)gps.getDay();
    toReturn.hour = (int)gps.getHour();
    toReturn.minute = (int)gps.getMinute();
    toReturn.second = (int)gps.getSecond();
    toReturn.hour = (int)gps.getHour();
    return toReturn;
}

int GPS::getSIV() {
    return gps.getSIV();
}
