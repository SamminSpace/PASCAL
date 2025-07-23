// #include <SparkFun_u-blox_GNSS_v3.h> //http://librarymanager/All#SparkFun_u-blox_GNSS_v3
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> 

#include "Timers.h"
#include "components/GPS.h"
#include "Config.h"
#include "Data.h"
#include "PASCAL.h"



void GPS::init() {
	Wire.setSDA(12);
	Wire.setSCL(13);
	Wire.begin();

    // Initialization
    if (!gps.begin()) {
		data.error = data.error > GPS_ERROR ? data.error : GPS_ERROR;	
		logger.writeError("GPS Initialization Error");
		return;	
    }

    // Updating settings
    gps.setI2COutput(COM_TYPE_UBX);
    gps.setNavigationFrequency(5);
    if (gps.setDynamicModel(DYN_MODEL_AIRBORNE4g) == false) {
		data.error = data.error > GPS_ERROR ? data.error : GPS_ERROR;	
		logger.writeError("Dynamic Model Incorrectly Set Error (GPS init)");
	}
    gps.saveConfiguration();

	// Waiting for a satellite lock
	long startTime = millis();
    while (gps.getSIV() < 3) {
        Serial.print("Waiting for lock, SIV: ");
		Serial.println(gps.getSIV());
		
		// Limiting the wait to 3 seconds
		if (millis() - startTime > 3000) break;
    }

}

void GPS::update() {

	// Checking for new data
	gps.checkUblox();
	if (gps.getPVT() == false) {
		return;  
	}
	
	data.gpsData.pos = { 
		((double)gps.getLongitude() * pow(10, -7)),
		((double)gps.getLatitude() * pow(10, -7)),
		gps.getAltitude() / 1000.0
	};

  	data.gpsData.SIV = gps.getSIV();
	data.gpsData.time = {
		(int)gps.getYear(),
		(int)gps.getMonth(),
		(int)gps.getDay(),
		(int)gps.getHour(),
		(int)gps.getMinute(),
		(int)gps.getSecond(),
	};
  
  	tick.reset();
}

int GPS::getSIV() {
	if (tick.isComplete()) {
		update();
	}
    return data.gpsData.SIV;
}

void GPS::updateData() {
	if (tick.isComplete()) {
		update();
	}
}
