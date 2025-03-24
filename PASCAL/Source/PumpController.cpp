
#include "../PumpController.h"


// Ensure that there are 6 solenoid pins
PumpController::PumpController(Config config) {

    // Setting pins
    for (int i = 0; i < sizeof(config.pins.solenoidPins)/sizeof(config.pins.solenoidPins[0]); i++) {
        solenoidPins[i] = config.pins.solenoidPins[i];
    }
    exhaustPin = config.pins.exhaustPin;
    pumpPin = config.pins.pumpPin;

    // Setting the samples
    for (int i = 0; i < sizeof(config.samplingAltitudes)/sizeof(config.samplingAltitudes[0]); i++) {

        Sample toAdd;

        // Updating the sample to match what we want
        // The default timer is 3 seconds and it starts not started, so we don't specify them
        toAdd.sampleAltitude = config.samplingAltitudes[i];
        toAdd.sampleNum = i;

        // Adding it to the array
        samples[i] = toAdd;

    }

}

void PumpController::init() {
    for (int i = 0; i < sizeof(solenoidPins)/sizeof(solenoidPins[0]); i++) {
        pinMode(solenoidPins[i], OUTPUT);
    }
    pinMode(exhaustPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
}

void PumpController::sampling(double altitude) {

    for (int i = 0; i < sizeof(samples)/sizeof(samples[0]); i++) {
        if (samples[i].sampleAltitude > altitude && samples[i].state != SampleState::COMPLETE) {
            takeSample(i);
        }
    }

}


void PumpController::takeSample(int sampleNum) {

    if (samples[sampleNum].state == SampleState::NOT_STARTED) {
        
        // Starting the sample
        samples[sampleNum].sampleTimer.reset();
        samples[sampleNum].state = SampleState::ACTIVE;
        digitalWrite(solenoidPins[sampleNum], HIGH);
        digitalWrite(pumpPin, HIGH);

    } else if (samples[sampleNum].state == SampleState::ACTIVE) {
        // Checking to see if the sample is done
        if (samples[sampleNum].sampleTimer.isComplete()) {
            // CLOSE SOLENOID AND UPDATE STATE TO COMPLETED
            // Ending the sample
            digitalWrite(pumpPin, LOW);
            digitalWrite(solenoidPins[sampleNum], LOW);

            // Switching to cleaning if there are no other samples active
            for (int i = 0; i < sizeof(samples)/sizeof(samples[0]); i++) {
                if (samples[i].state == SampleState::ACTIVE && i != sampleNum) {
                    samples[i].state = SampleState::COMPLETE;
                    return;
                }
            }

            // Setting it to cleaning
            samples[sampleNum].sampleTimer.reset();
            samples[sampleNum].state = SampleState::CLEANING;
        
            // Beginning the cleaning
            digitalWrite(exhaustPin, LOW);

        }
    } else if (samples[sampleNum].state == SampleState::CLEANING) {
        if (samples[sampleNum].sampleTimer.isComplete()) {
            
            // Stopping the cleaning
            digitalWrite(pumpPin, LOW);
            digitalWrite(exhaustPin, HIGH);

            // Telling the sample that it is done.
            samples[sampleNum].state = SampleState::COMPLETE;

        }
    }

}
