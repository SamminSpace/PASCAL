
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
        Serial.println("EXHAUSR OPEN");

        // Running the pump
        digitalWrite(pumpPin, HIGH);
        Serial.println("PUMP ON");

        // Starting the timer for cleaning
        samples[sampleNum].sampleTimer.reset();
        Serial.println("Sample Timer Started");

        // Setting the state
        samples[sampleNum].state = SampleState::CLEANING;
        Serial.println("CLEANING");

        
        // Starting the sample
        // samples[sampleNum].sampleTimer.reset();
        // samples[sampleNum].state = SampleState::ACTIVE;
        // digitalWrite(solenoidPins[sampleNum], HIGH);
        // digitalWrite(pumpPin, HIGH);
        // digitalWrite(exhaustPin, LOW);

    } else if (samples[sampleNum].state == SampleState::CLEANING) {
        if (samples[sampleNum].sampleTimer.isComplete()) {
            
            // Stopping the cleaning
            digitalWrite(exhaustPin, LOW);
            Serial.println("EXHAUST CLOSE");

            // Waiting like a half second
            samples[sampleNum].cleaningTimer.reset();
            Serial.println("Cleaning Timer Started");

            // Changing the state
            samples[sampleNum].state = SampleState::ACTIVE;
            Serial.println("ACTIVE");

            // Starting the sample timer to show that it needs to run next iteration
            samples[sampleNum].sampleTimer.reset();

        } 
    }
    
    else if (samples[sampleNum].state == SampleState::ACTIVE) {

        // Checking to see if it is time to start sampling
        if (samples[sampleNum].cleaningTimer.isComplete()) {

          // Closing the exhaust
          digitalWrite(exhaustPin, LOW);
          Serial.println("EXHAUST CLOSED STILL");

          // Checking to see if we are done sampling
          if (samples[sampleNum].sampleTimer.isComplete()) {

            // Close the sample
            digitalWrite(solenoidPins[sampleNum], LOW);
            Serial.println("SOLENOID CLOSED ");


            // Turning off the pump
            digitalWrite(pumpPin, LOW);
            Serial.println("PUMP OFF");


            // Changing state
            samples[sampleNum].state = SampleState::COMPLETE;
            Serial.println("COMPLETE");

          } else if (!samples[sampleNum].hasSampleStarted) {
              // Starting the sample
            samples[sampleNum].sampleTimer.reset();
            samples[sampleNum].hasSampleStarted = true;
            Serial.println("Seal finsihed; Starting Sample");
            digitalWrite(solenoidPins[sampleNum], HIGH);
            Serial.println("SOLENOID ON");


          }

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
      }
  }
  return "PASSIVE";
}
