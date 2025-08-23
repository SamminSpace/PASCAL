#include <SD.h>
#include <string>
#include "Config.h"
#include "Data.h"
#include "PASCAL.h"
#include "components/Logger.h"

Logger::Logger(const char* prefix) {

	// Making a new file and ensuring it exits (Thanks for the code HAVOC)
	// Start with number 1
	unsigned short int fileNumber = 1;
	// Reserve space for filenames up to 31 chars
	char name[32];
	// Same but for the errors
	char errorName[32];
	// Reserve space for converting number to string
	char fileNumberStr[6];
	do {
        // Overwrite fileName with prefix
        strcpy(name, prefix);
        // Convert fileNumber to five-char string (e.g. 1 -> 00001)
        sprintf(fileNumberStr, "%0*d", 5, fileNumber);
        // Append fileNumber to prefix
        strcat(name, fileNumberStr);
		// Copy to error file
		strcpy(errorName, name);
        // Append ".csv" to file name
        strcat(name, ".csv");
		// Append "-Errors.csv" to error file name
		strcat(errorName, "-Errors.csv");
        // Increment the filenumber for next loop
        fileNumber++;
    } while (SD.exists(name) && SD.exists(errorName)); // Do that again if the file exists already

	// Saving the file name we found
	fileName = name;

	// Saving an extra file name as the same thing with a -Errors tag
	errorFileName = errorName;
}

void Logger::init() {
    if (!SD.begin(config.pins.chipSelect)) {
        data.error = data.error > SD_ERROR ? data.error : SD_ERROR;
		return;   
    }

	// Writes the header for the file
	write("Payload,Payload State,Sampling State,Packet Number,Mission Time (s),SIV,UTC Time,Oxygen Concentration (ppb),Temperature (deg C),Humidity (%),Humidity Sensor Temperature (deg C),Pressure (mBar),GPS Altitude (m),GPS Latitude (DD.dddd),GPS Longitude (DD.dddd),Nitrogen (ppb),Aux Measure (mV),WE Measure (mV),Error"); 

	// Writes the header for the error file 
	File dataFile = SD.open(errorFileName, FILE_WRITE);
    if (dataFile) {
        dataFile.println("Mission Time,Error Name,Altitude,Flight State,Sample State");
        dataFile.close();
    }

	
}

void Logger::write(String toWrite) {
    File dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
        dataFile.println(toWrite);
        dataFile.close();
    } else {
		writeError("`write` Function Failed on Opening Error");
	}
}

void Logger::writeError(String errorName) {

	// Adding context
	String toWrite = String(data.missionTime)
		+ errorName + ","
		+ String(data.atmoData.alt) + ","
		+ getFlightStateString(data.state) + ","
		+ getSampleStateString(data.sampleState);

	// Writing the data
	File dataFile = SD.open(errorFileName, FILE_WRITE);
    if (dataFile) {
        dataFile.println(toWrite);
        dataFile.close();
    }
}

void Logger::writeTelemetry() {

	// future reference: nitrogen, Aux, WE
	String Data = config.payload + "," + 
	getFlightStateString(data.state) + "," + 
	getSampleStateString(data.sampleState) + "," +
	String(data.packetNumber) + "," + 
	String(data.missionTime) + "," + 
	String(data.gpsData.SIV) + "," + 
	String(data.gpsData.time.year) + ":" + String(data.gpsData.time.month) + ":" + String(data.gpsData.time.day) + ":" + 
	String(data.gpsData.time.hour) + ":" + String(data.gpsData.time.minute) + ":" + String(data.gpsData.time.second) + "," + 
	String(data.atmoData.oxygen) + "," + 
	String(data.atmoData.temperature) + "," + 
	String(data.atmoData.humidity) + "," + 
	String(data.atmoData.humiditySensorTemperature) + "," + 
	String(data.atmoData.pressure) + "," + 
	String(data.gpsData.pos.alt) + "," + 
	String(data.gpsData.pos.lat) + "," + 
	String(data.gpsData.pos.lon) + "," +
	String(data.atmoData.no2) + "," +
	String(data.Aux_real) + "," +
	String(data.WE_real) + "," +
	getErrorString(data.error);	
	write(Data);
  
	data.packetNumber++;
}
  

