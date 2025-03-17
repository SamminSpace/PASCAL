
#include "Source/PumpController.cpp"


// Ensure that there are 6 solenoid pins
PumpController::PumpController(int solenoidPins[], int exhaustPin, int pumpPin) {

    this->solenoidPins = solenoidPins;
    this->exhaustPin = exhaustPin;
    this->pumpPin = pumpPin;

}

void PumpController::init() {
    for (int i = 0; i < sizeof(solenoidPins)/sizeof(int); i++) {
        pinMode(solenoidPins[i], OUTPUT);
    }
    pinMode(exhaustPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
}

void PumpController::trigger(int sampleNumber) {
    // TODO Code for sampling here, will be inputted with more testing
}

