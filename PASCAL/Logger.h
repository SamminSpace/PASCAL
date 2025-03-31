#ifndef LOGGER_H
#define LOGGER_H

// #include <string>
#include "Config.h"


class Logger {
private:
    String fileName;

    // TODO add in stuff to write the telemetry nicely

public:

    // Creates a new logger object
    // Note that the filename should NOT include.txt
    Logger(String fileNameToWrite);

    // Initializes the logger
    errorState init(int chipSelect);

    // Writes something to the logger
    void write(String toWrite);

    // Adds the header to the file
    void writeHead();
    
};
#endif