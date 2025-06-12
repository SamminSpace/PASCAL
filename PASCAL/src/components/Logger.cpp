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
	// Reserve space for converting number to string
	char fileNumberStr[6];
	do {
        // Overwrite fileName with prefix
        strcpy(name, prefix);
        // Convert fileNumber to five-char string (e.g. 1 -> 00001)
        sprintf(fileNumberStr, "%0*d", 5, fileNumber);
        // Append fileNumber to prefix
        strcat(name, fileNumberStr);
        // Append ".csv" to file name
        strcat(name, ".csv");
        // Increment the filenumber for next loop
        fileNumber++;
    } while (SD.exists(name)); // Do that again if the file exists already

	// Saving the file name we found
	fileName = name;

}

void Logger::init() {
    if (!SD.begin(config.pins.chipSelect)) {
        data.error = data.error > SD_ERROR ? data.error : SD_ERROR;
		return;   
    }


	// TODO Add a header write here
	
}

void Logger::write(String toWrite) {
    File dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
        dataFile.println(toWrite);
        dataFile.close();
    }
}

void Logger::writeTelemetry() {
	// TODO
}

