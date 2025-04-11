
#include "PumpController.h"
#include "Config.h"
#include <Arduino.h>

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
        toAdd.sampleAltitude = config.samplingAltitudes[i];
        toAdd.sampleNum = i;

        // creating the timers for each
        toAdd.sampleTimer = Timer(config.sampleLengths[i]);       

        // Adding it to the array
        samples[i] = toAdd;

    }

}

errorState PumpController::init() {
    for (int i = 0; i < sizeof(solenoidPins)/sizeof(solenoidPins[0]); i++) {
        pinMode(solenoidPins[i], OUTPUT);
    }
    pinMode(exhaustPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
    return NO_ERROR;
}


//Turns each solenoid on for 0.5 second and then closes
void PumpController::pattern() {  

   if (!patternDone){ 
   digitalWrite(solenoidPins[0], HIGH);
   delay(500);
   digitalWrite(solenoidPins[0], LOW);
   digitalWrite(solenoidPins[1], HIGH);
   delay(500);
   digitalWrite(solenoidPins[1], LOW);
   digitalWrite(solenoidPins[2], HIGH);
   delay(500);
   digitalWrite(solenoidPins[2], LOW);
   digitalWrite(solenoidPins[3], HIGH);
   delay(500);
   digitalWrite(solenoidPins[3], LOW);
   digitalWrite(solenoidPins[4], HIGH);
   delay(500);
   digitalWrite(solenoidPins[4], LOW);
   digitalWrite(solenoidPins[5], HIGH);
   delay(500);
   digitalWrite(solenoidPins[5], LOW);
   digitalWrite(exhaustPin, HIGH);
   delay(500);
   digitalWrite(exhaustPin, LOW);
   patternDone = true;
   }

}


void PumpController::sampling(double altitude) {
 
    for (int i = 0; i < sizeof(samples)/sizeof(samples[0]); i++) {
        if (samples[i].sampleAltitude < altitude && samples[i].state != SampleState::COMPLETE) {
            takeSample(i);
        }
    }

}


void PumpController::takeSample(int sampleNum) {

    if (samples[sampleNum].state == SampleState::NOT_STARTED) {

        // Cleaning it out first

        // Opening the exhaust
        digitalWrite(exhaustPin, HIGH);
        // Serial.println("EXHAUST OPEN");

        // Running the pump
        digitalWrite(pumpPin, HIGH);
        // Serial.println("PUMP ON");

        // Starting the timer for cleaning
        samples[sampleNum].cleaningTimer.reset();
        // Serial.println("Cleaning Timer Started");

        // Setting the state
        samples[sampleNum].state = SampleState::CLEANING;
        // Serial.println("CLEANING");
        
    } else if (samples[sampleNum].state == SampleState::CLEANING) {
        if (samples[sampleNum].cleaningTimer.isComplete()) {
            
            // Stopping the cleaning
            digitalWrite(exhaustPin, LOW);
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

            // Serial.println("Seal finsihed; Starting Sample");

            // Beginning the sample            
            digitalWrite(solenoidPins[sampleNum], HIGH);
            samples[sampleNum].sampleTimer.reset();
            samples[sampleNum].state = SampleState::ACTIVE;

            // Serial.println("SOLENOID ON");

        }
    
    } else if (samples[sampleNum].state == SampleState::ACTIVE) {

        // Checking to see if it is time to start sampling
        if (samples[sampleNum].sampleTimer.isComplete()) {

            // Stopping the sample
            digitalWrite(solenoidPins[sampleNum], LOW);
            // Serial.println("SOLENOID CLOSED ");

            // Turning off the pump
            digitalWrite(pumpPin, LOW);
            // Serial.println("PUMP OFF");

            // Changing state
            samples[sampleNum].state = SampleState::COMPLETE;
            // Serial.println("COMPLETE");

        }

    } 

}

// A getter for the sample status 
String PumpController::getSampleStatus() {
  for (int i = 0; i < sizeof(samples)/sizeof(samples[0]); i++) {
      if(samples[i].state == SampleState::ACTIVE){
        return "SAMPLING";
      } else if (samples[i].state == SampleState::CLEANING) {
        return "CLEANING";
      } else if (samples[i].state == SampleState::SEALING) {
        return "SEALING";
      }
  }
  return "PASSIVE";
}
