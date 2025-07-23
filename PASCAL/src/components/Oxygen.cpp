
#include "components/Oxygen.h"
#include "PASCAL.h"

void OxygenSensor::init() {
    if(!oxygen.begin(ADDRESS_3)){
		    data.error = data.error > O2_ERROR ? data.error : O2_ERROR;
        logger.writeError("Oxygen Sensor Initialiazation Error");
    }
}

void OxygenSensor::updateData() {
    data.atmoData.oxygen = oxygen.getOxygenData(collectionNumber);
}
