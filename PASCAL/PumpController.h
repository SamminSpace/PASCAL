#ifndef PUMPCONTROLLER_H
#define PUMPCONTROLLER_H

#include "Time.h"
#include "Config.h"

// Describes the samples as to whether they are running, done, or not started yet
enum class SampleState {
    NOT_STARTED,    // 0
    ACTIVE,         // 1
    COMPLETE,       // 2
    CLEANING        // 3
};


struct Sample {

    // The state of the sample (probably didn't need that comment but whatever)
    SampleState state = SampleState::NOT_STARTED;

    // The altitude to sample at
    long sampleAltitude;

    // How long the sample will run
    Timer sampleTimer = Timer(3000);

    // The sample ID, AKA the index in the array
    int sampleNum;

    // ! Honestly it might be wise to add a solenoid pin here to make it even more readable

};


class PumpController {
private:

    // NOTE: These are not scalable though I think there should be a way to make them easily scalable in the future

    // The pins
    int solenoidPins[6];
    int numberOfSolenoids;
    int pumpPin;
    int exhaustPin;

    // The samples
    Sample samples[6];
    int numberOfSamples;

    // A function to run a specific sample 
    // (private because they are meant to be accessed through the sampling function)
    void takeSample(int sampleNum);

public:

    // Creates a new controller bound to the pins
    PumpController(Config config);

    // Initializes the pins to be output
    errorState init();

    // Runs the sampling
    void sampling(double altitude);

};
#endif
