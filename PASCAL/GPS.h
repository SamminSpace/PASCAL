#ifndef GPS_H
#define GPS_H

#include "Time.h"
#include <optional>
// #include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 
#include "Config.h"

// A UTC time struct for data organization
struct UTCTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};


class GPS {
private: 
    SFE_UBLOX_GNSS gps;
    int gnssAddress = 0x42;

    // The timer 
    Timer tick = Timer(1000);

    // Cached data 
    UTCTime time;
    double altitude = -1.0;
    double longitude = -1.0;
    double latitude = -1.0;
    int siv;

    // An internal function to update the data when the tick is hit
    void update();

public:

    // Initializes the GPS
    errorState init();

    // Returns the altitude
    float getAltitude();

    // Returns the longitude
    float getLongitude();

    // Returns the latitude
    float getLatitude();

    // Returns the UTC time
    UTCTime getUTCTime();

    // Returns the number of satellites locked onto 
    int getSIV();

};

#endif
