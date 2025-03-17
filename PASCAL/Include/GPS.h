#pragma once


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
    Timer tick = Timer(1000); // ms
    int gnssAddress = 0x42;

public:

    // Initializes the GPS (auto-called by the constructor)
    void init();

    // Returns an optional position in the form of an array [altitude, longitude, latitude]
    std::optional<double[3]> getPosition();

    std::optional<UTCTime> getUTCTime();

    // Returns the number of satellites locked onto 
    std::optional<int> getSIV();

};
