int smol = 7;
int tiny = 8;

int error = 6;
int period = 500;
int blinker;

unsigned long startMillis;

void setup() {
   Serial.begin(9600);
   pinMode(smol, OUTPUT);
   pinMode(tiny, OUTPUT);
  startMillis = millis();
}

void loop() {
 Serial.print("Checking.... ");

  if (error == 1){		//error 1 will be SD (all on)
    Serial.println("SD failed! Why? idk go fix it.");
    digitalWrite(tiny, HIGH);
    digitalWrite(smol, HIGH);
    
  } else if (error == 2){   //error 2 is GPS (1 on/off)
    Serial.println("Hey, your GPS is messed up!");
    digitalWrite(tiny, HIGH);
    digitalWrite(smol, LOW);
    
  } else if (error == 3){   //BMP (other on/off)
    Serial.println("BMP not found.");
    digitalWrite(tiny, LOW);
    digitalWrite(smol, HIGH);
    
  } else if (error == 4){  // NO2 (tiny blinks and smol on)
    Serial.println("NO2 (the problem child) is not functioning");
    digitalWrite(smol, HIGH);
    blinker = tiny;
    Blinky();
    
  } else if (error == 5){  //Humidity (smol blinks and tiny on)
    Serial.println("Must be too dry bc humidty not detected.");
    digitalWrite(tiny, HIGH);
    blinker = smol;
    Blinky();
     
  } else if (error == 6){   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
    Serial.println("Apparently no oxygen found so idk how you are alive rn");
    digitalWrite(tiny, LOW);
    blinker = smol;
    Blinky();
  } else{
    Serial.println("lets go!");
    digitalWrite(tiny, LOW);
    digitalWrite(smol, LOW);
    
  }
    
}  
    

void Blinky() {
  unsigned long currentMillis;
  
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    digitalWrite(blinker, !digitalRead(blinker));  //if so, change the state of the LED.  Uses a neat trick to change the state
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  } 
}
 
