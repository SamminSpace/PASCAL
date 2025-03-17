#pragma once


class PumpController {
private:
    int solenoidPins[6];
    int pumpPin;
    int exhaustPin;

public:

    // Creates a new controller bound to the pins
    PumpController(int solenoidPins[], int exhaustPin, int pumpPin);

    // Initializes the pins to be output
    void init();

    // Triggers a sampling with this bag
    void trigger(int sampleNumber);

};

