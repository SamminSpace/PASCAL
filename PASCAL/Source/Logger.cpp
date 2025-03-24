// #include <Wire.h>
#include <SD.h>
#include <string>
// #include <SPI.h>
// #include <Adafruit_BMP3XX.h>
// #include "DFRobot_OxygenSensor.h"

#include "../Logger.h"

Logger::Logger(String fileNameToWrite) {
    fileName = fileNameToWrite;
}

void Logger::init() {
    if (!SD.begin(chipSelect)) {
        error = SD_ERROR;   
    }
}

void Logger::write(String toWrite) {
    File dataFile = SD.open(fileName + ".txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println(openingString);
        dataFile.close();
    } 
    // TODO optional error codes here
}

void Logger::writeHead() {
    String openingString = " ________  ________  ________  ________  ________  ___          \n|\\   __  \\|\\   __  \\|\\   ____\\|\\   ____\\|\\   __  \\|\\  \\         \n\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\___|\\ \\  \\|\\  \\ \\ \\        \n \\ \\   ____\\ \\   __  \\ \\_____  \\ \\  \\    \\ \\   __  \\ \\  \\       \n  \\ \\  \\___|\\ \\  \\ \\  \\|____|\\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\____  \n   \\ \\__\\    \\ \\__\\ \\__\\____\\_\\  \\ \\_______\\ \\__\\ \\__\\ \\_______\\n    \\|__|     \\|__|\\|__|\\_________\\|_______|\\|__|\\|__|\\|_______|\n                       \\|_________|                             \n                                                                                                                                \n";

    File dataFile = SD.open(fileName + ".txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println(openingString);
        dataFile.close();
    } 


}
