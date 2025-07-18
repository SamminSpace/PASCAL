#ifndef GPS_H
#define GPS_H

#include "Timers.h"
#include <optional>
// #include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 
#include "Config.h"
#include "Data.h"

class GPS {
private: 
    SFE_UBLOX_GNSS gps;
    int gnssAddress = 0x42;

	
    // The timer for the tick of the GPS
    Timer tick = Timer(1000);

    // An internal function to update the data when the tick is hit
    void update();

public:

    // Initializes the GPS
    void init();

    // Returns the number of satellites locked onto 
    int getSIV();

	// Updates the data from the GPS if the tick is ready
	void updateData();

};

#endif
