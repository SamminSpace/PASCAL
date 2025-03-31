int smol = 7;
int tiny = 8;

int period = 500;
int blinker;

enum errorState
{
  NO_ERROR,
  SD_ERROR,
  GPS_ERROR,
  BMP_ERROR,
  NO2_ERROR,
  HUMID_ERROR,
  O2_ERROR
};

errorState error;

unsigned long startMillis;

void setup() {
   Serial.begin(9600);
   pinMode(smol, OUTPUT);
   pinMode(tiny, OUTPUT);
  startMillis = millis();
}

void loop() {
 Serial.print("Checking.... ");
 
  if (error == SD_ERROR){		//error 1 will be SD (all on)
    Serial.println("SD failed! Why? idk go fix it.");
    digitalWrite(tiny, HIGH);
    digitalWrite(smol, HIGH);
    
  } else if (error == GPS_ERROR){   //error 2 is GPS (1 on/off)
    Serial.println("Hey, your GPS is messed up!");
    digitalWrite(tiny, HIGH);
    digitalWrite(smol, LOW);
    
  } else if (error == BMP_ERROR){   //BMP (other on/off)
    Serial.println("BMP not found.");
    digitalWrite(tiny, LOW);
    digitalWrite(smol, HIGH);
    
  } else if (error == NO2_ERROR){  // NO2 (tiny blinks and smol on)
    Serial.println("NO2 (the problem child) is not functioning");
    digitalWrite(smol, HIGH);
    blinker = tiny;
    Blinky();
    
  } else if (error == HUMID_ERROR){  //Humidity (smol blinks and tiny on)
    Serial.println("Must be too dry bc humidty not detected.");
    digitalWrite(tiny, HIGH);
    blinker = smol;
    Blinky();
     
  } else if (error == O2_ERROR){   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
    Serial.println("Apparently no oxygen found so idk how you are alive rn");
    digitalWrite(tiny, LOW);
    blinker = smol;
    Blinky();
  } else{
    Serial.println("lets go!");
    digitalWrite(tiny, LOW);
    digitalWrite(smol, LOW);
    
  }
    Serial.println(error);
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
 
