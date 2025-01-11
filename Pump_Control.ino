int exhaustPin = 9;  //all these are temporary pins
int solenoid1 = 1;   //need to look at electrical diagrams first
int solenoid2 = 2;
int solenoid3 = 3;  //possibly use array here?
int solenoid4 = 4;
int solenoid5 = 5;
int solenoid6 = 6;
int Pump = 18;

int pumpTimer = 0;


void setup() {
 pinMode(exhaustPin, OUTPUT);
 pinMode(solenoid1, OUTPUT);
 pinMode(solenoid2, OUTPUT);
 pinMode(solenoid3, OUTPUT);
 pinMode(solenoid4, OUTPUT);
 pinMode(solenoid5, OUTPUT);
 pinMode(solenoid6, OUTPUT);
 pinMode(Pump, OUTPUT);

 digitalWrite(exhaustPin, HIGH); //open exhaust in start up to clear airway
 digitalWrite(solenoid1, LOW);
 digitalWrite(solenoid2, LOW);
 digitalWrite(solenoid3, LOW);
 digitalWrite(solenoid4, LOW);
 digitalWrite(solenoid5, LOW);
 digitalWrite(solenoid6, LOW);
 digitalWrite(Pump, LOW);      //turn off pump and close all samples

Serial.begin();
}

void loop() {
  digitalWrite(exhaustPin, LOW);
  digitalWrite(solenoid1, HIGH);
  digitalWrite(Pump, HIGH);
  Serial.println("Begin sample taking.");

  pumpTimer = (millis() / 1000); //start timer 
    

  if (pumpTimer >= PumpTimer()){ //when timer reaches the needed value, end sample
    digitalWrite(Pump, LOW);
    digitalWrite(solenoid1, LOW);
    digitalWrite(exhaustPin, HIGH);
    Serial.println("Sample has completed.");
    pumpTimer = 0;
    return; //stop code
  }

}


int PumpTimer(){    //returns how long the pump should be turned on for
  int pumpOn = 15; //pump should stay on for 10-20 seconds

  /* In reality, we will do testing to determine the correct 
  amount of time that the pump will stay on. Then we shall have
  the fancy math here */

  return pumpOn;
}
