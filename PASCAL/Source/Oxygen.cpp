
#include "Inlcude/Oxygen.h"



void OxygenSensor::init() {
    while(!oxygen.begin(ADDRESS_3)){
        delay(1000);
        // TODO error codes
    }
}

float OxygenSensor::getOxygen() {
    return oxygenData = oxygen.getOxygenData(collectionNumber);

}