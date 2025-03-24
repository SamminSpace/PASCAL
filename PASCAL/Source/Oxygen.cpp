
#include "../Oxygen.h"


void OxygenSensor::init() {
    if(!oxygen.begin(ADDRESS_3)){
        error = O2_ERROR;
    }
}

float OxygenSensor::getOxygen() {
    return oxygenData = oxygen.getOxygenData(collectionNumber);

}
