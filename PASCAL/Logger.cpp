// #include <Wire.h>
#include <SD.h>
#include <string>
// #include <SPI.h>
// #include <Adafruit_BMP3XX.h>
// #include "DFRobot_OxygenSensor.h"
#include "Config.h"
#include "Logger.h"

Logger::Logger(String fileNameToWrite) {
    fileName = fileNameToWrite;
}

errorState Logger::init(int chipSelect) {
    if (!SD.begin(chipSelect)) {
        return SD_ERROR;   
    }
    return NO_ERROR;
}

void Logger::write(String toWrite) {
    File dataFile = SD.open(fileName + ".csv", FILE_WRITE);
    if (dataFile) {
        dataFile.println(toWrite);
        dataFile.close();
    } 
}


// void Logger::writeHead() {
//     File dataFile = SD.open(fileName + ".csv", FILE_WRITE);
//     if (dataFile) {
//         dataFile.println(openingString);
//         dataFile.close();
//     } 


// } 
