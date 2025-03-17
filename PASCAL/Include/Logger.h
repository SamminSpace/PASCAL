#pragma once

class Logger {
private:
    string fileName;
    SD nativeObject;

    // TODO add in stuff to write the telemetry nicely

public:

    // Creates a new logger object
    // Note that the filename should NOT include.txt
    Logger(string fileNameToWrite);

    // Initializes the logger
    void init();

    // Writes something to the logger
    void write(string toWrite);

    // Adds the header to the file
    void writeHead();
    
};