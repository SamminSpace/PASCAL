#pragma once

#include "Config.h"
#include "Data.h"

class Logger {
private:
    char* fileName;
    char* errorFileName;
public:

    // Creates a new logger object
    // Note that the filename should NOT include.txt
    Logger(const char* prefix);

    // Initializes the logger
    void init();

    // Writes something to the logger
    void write(String toWrite);

    // Writes an error to the error file
    void writeError(String errorName);

	// Writes all of the data we currently have to the SD
	void writeTelemetry();

};
