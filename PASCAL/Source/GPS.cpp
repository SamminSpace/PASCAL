#include <SparkFun_u-blox_GNSS_v3.h> //http://librarymanager/All#SparkFun_u-blox_GNSS_v3

#include "Time.cpp"
#include "GPS.h"
#include <optional>


void GPS::init() {
    // Optional debug statements are commented out

    // Initialization
    while (!gps.begin()) {
        // TODO Error codes
        delay(1000);
    }

    // Updating settings
    gps.setI2COutput(COM_TYPE_UBX);
    gps.setNavigationFrequency(5);
    if (gps.setDynamicModel(DYN_MODEL_AIRBORNE4g) == false) {
        // TODO Error codes
    }
    gps.saveConfiguration();

    while (gps.getSIV() < 3) {
        delay(1000);
        // TODO Error codes
    }

}

std::optional<double[3]> GPS::getPosition() {
    if (tick.isComplete()) {
        double toReturn[3];
        toReturn[0] = gps.getAltitude() / 1000.0;
        toReturn[1] = ((double)gps.getLongitude()) * pow(10, -7);
        toReturn[2] = ((double)gps.getLatitude()) * pow(10, -7);
        return toReturn;
    }
    return std::nullopt;
}

std::optional<UTCTime> GPS::getUTCTime() {
    if (tick.isComplete()) {
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
    return std::nullopt;
}

std::optional<int> GPS::getSIV() {
    if (tick.isComplete()) {
        return gps.getSIV();
    }
    return std::nullopt;
}
