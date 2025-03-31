
#include "Oxygen.h"
#include "Config.h"

errorState OxygenSensor::init() {
    if(!oxygen.begin(ADDRESS_3)){
        return O2_ERROR;
    }
    return NO_ERROR;
}

float OxygenSensor::getOxygen() {
    return oxygen.getOxygenData(collectionNumber);

}
