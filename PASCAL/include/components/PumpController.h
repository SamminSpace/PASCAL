#pragma once

#include "Timers.h"
#include "Data.h"
#include "Config.h"


struct Sample {

    // The state of the sample (probably didn't need that comment but whatever)
    SampleState state = SampleState::NOT_STARTED;

    // The altitude to sample at
    long sampleAltitude;

    // How long the sample will run
    Timer sampleTimer = Timer(1000);

    // The sealing timer, defaults to a quarter of a second
    Timer sealingTimer = Timer(250);

    // The cleaning timer, defaults to half a second
    Timer cleaningTimer = Timer(500);

    // The sample ID, AKA the index in the array
    int sampleNum;

	// The pin controlling this sample's solenoid
	int solenoidPin;

};


class PumpController {
private:

    // NOTE: These are not scalable though I think there should be a way to make them easily scalable in the future

    // The pins
    // int solenoidPins[6];
    // int numberOfSolenoids;
    // int pumpPin;
    // int exhaustPin;

    // The samples
    Sample samples[6];
    // int numberOfSamples;

	// Records whether the init pattern is done or not
	bool patternDone = false;

    // A function to run a specific sample 
    // (private because they are meant to be accessed through the sampling function)
    void takeSample(int sampleNum);

public:

    // Creates a new controller bound to the pins
    PumpController();

    // Initializes the pins to be output
    void init();


    void pattern();

    // Runs the sampling
    void sampling();

};

