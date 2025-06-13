
#include "components/PumpController.h"
#include "Config.h"
#include "PASCAL.h"
#include <Arduino.h>

// Ensure that there are 6 solenoid pins
PumpController::PumpController() {

    // Setting the samples
    for (int i = 0; i < sizeof(config.samplingAltitudes)/sizeof(config.samplingAltitudes[0]); i++) {

        Sample toAdd;

        // Updating the sample to match what we want
        toAdd.sampleAltitude = config.samplingAltitudes[i];
        toAdd.sampleNum = i;

        // Creating the timers for each
        toAdd.sampleTimer = Timer(config.sampleLengths[i]);    
		toAdd.cleaningTimer = Timer(config.cleaningLengths[i]);
		toAdd.sealingTimer = Timer(config.sealingLengths[i]);

		// Adding the solenoid pin
		toAdd.solenoidPin = config.pins.solenoidPins[i];

        // Adding it to the array
        samples[i] = toAdd;

    }

}

void PumpController::init() {
    for (int i = 0; i < sizeof(samples)/sizeof(samples[i]); i++) {
        pinMode(samples[i].solenoidPin, OUTPUT);
    }
    pinMode(config.pins.exhaustPin, OUTPUT);
    pinMode(config.pins.pumpPin, OUTPUT);

	// Automatically starting the pattern
	pattern();
}


//Turns each solenoid on for 0.5 second and then closes
void PumpController::pattern() {  

	// TODO make this scalable

	if (!patternDone){ 
		digitalWrite(samples[0].solenoidPin, HIGH);
		delay(500);
		digitalWrite(samples[0].solenoidPin, LOW);
		digitalWrite(samples[1].solenoidPin, HIGH);
		delay(500);
		digitalWrite(samples[1].solenoidPin, LOW);
		digitalWrite(samples[2].solenoidPin, HIGH);
		delay(500);
		digitalWrite(samples[2].solenoidPin, LOW);
		digitalWrite(samples[3].solenoidPin, HIGH);
		delay(500);
		digitalWrite(samples[3].solenoidPin, LOW);
		digitalWrite(samples[4].solenoidPin, HIGH);
		delay(500);
		digitalWrite(samples[4].solenoidPin, LOW);
		digitalWrite(samples[5].solenoidPin, HIGH);
		delay(500);
		digitalWrite(samples[5].solenoidPin, LOW);
		digitalWrite(config.pins.exhaustPin, HIGH);
		delay(500);
		digitalWrite(config.pins.exhaustPin, LOW);
		patternDone = true;
	}

}


void PumpController::sampling() {

	// Assuming that all the samples are not started yet until we're proven wrong
	data.sampleState = SampleState::COMPLETE;
 
    for (int i = 0; i < sizeof(samples)/sizeof(samples[0]); i++) {
        
		// Running the samples
		if (samples[i].sampleAltitude < data.gpsData.pos.alt && samples[i].state != SampleState::COMPLETE) {
            takeSample(i);
        }

		// Updating the sample state in the telemetry
		if (samples[i].state != SampleState::NOT_STARTED && samples[i].state != SampleState::COMPLETE) {
			data.sampleState = samples[i].state;
		}

    }

}


void PumpController::takeSample(int sampleNum) {

    if (samples[sampleNum].state == SampleState::NOT_STARTED) {

        // Cleaning it out first

        // Opening the exhaust
        digitalWrite(config.pins.exhaustPin, HIGH);

        // Running the pump
        digitalWrite(config.pins.pumpPin, HIGH);

        // Starting the timer for cleaning
        samples[sampleNum].cleaningTimer.reset();

        // Setting the state
        samples[sampleNum].state = SampleState::CLEANING;
        
    } else if (samples[sampleNum].state == SampleState::CLEANING) {
        if (samples[sampleNum].cleaningTimer.isComplete()) {
            
            // Stopping the cleaning
            digitalWrite(config.pins.exhaustPin, LOW);
            // Serial.println("EXHAUST CLOSE");

            // Waiting like a half second
            samples[sampleNum].sealingTimer.reset();
            // Serial.println("Sealing Timer Started");

            // Changing the state
            samples[sampleNum].state = SampleState::SEALING;
            // Serial.println("SEALING");

        } 
    } else if (samples[sampleNum].state == SampleState::SEALING) {

        // Checking if the thing has sealed yet
        if (samples[sampleNum].sealingTimer.isComplete()) {

            // Serial.println("Seal finished; Starting Sample");

            // Beginning the sample            
            digitalWrite(samples[sampleNum].solenoidPin, HIGH);
            samples[sampleNum].sampleTimer.reset();
            samples[sampleNum].state = SampleState::ACTIVE;

            // Serial.println("SOLENOID ON");

        }
    
    } else if (samples[sampleNum].state == SampleState::ACTIVE) {

        // Checking to see if it is time to start sampling
        if (samples[sampleNum].sampleTimer.isComplete()) {

            // Stopping the sample
            digitalWrite(samples[sampleNum].solenoidPin, LOW);
            // Serial.println("SOLENOID CLOSED ");

            // Turning off the pump
            digitalWrite(config.pins.pumpPin, LOW);
            // Serial.println("PUMP OFF");

            // Changing state
            samples[sampleNum].state = SampleState::COMPLETE;
            // Serial.println("COMPLETE");

        }

    } 

}

