#pragma once

// #include <string>


class Logger {
private:
    String fileName;

    // TODO add in stuff to write the telemetry nicely

public:

    // Creates a new logger object
    // Note that the filename should NOT include.txt
    Logger(String fileNameToWrite);

    // Initializes the logger
    void init();

    // Writes something to the logger
    void write(String toWrite);

    // Adds the header to the file
    void writeHead();
    
};