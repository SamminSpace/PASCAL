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

unsigned long beginMillis;

void setup() {
   Serial.begin(9600);
   pinMode(smol, OUTPUT);
   pinMode(tiny, OUTPUT);
  startMillis = millis();
}

void loop() {
 
  Switch(error){		//error 1 will be SD (all on)
    case SD_ERROR:
    digitalWrite(tiny, HIGH);
    digitalWrite(smol, HIGH);
    break;
    
    case GPS_ERROR:  //error 2 is GPS (1 on/off)
    Serial.println("Hey, your GPS is messed up!");
    digitalWrite(tiny, HIGH);
    digitalWrite(smol, LOW);
    break;
    
    case BMP_ERROR:   //BMP (other on/off)
    Serial.println("BMP not found.");
    digitalWrite(tiny, LOW);
    digitalWrite(smol, HIGH);
    break;
    
   case NO2_ERROR:  // NO2 (tiny blinks and smol on)
    Serial.println("NO2 (the problem child) is not functioning");
    digitalWrite(smol, HIGH);
    blinker = tiny;
    Blinky();
    breal;
    
    case HUMID_ERROR:  //Humidity (smol blinks and tiny on)
    Serial.println("Must be too dry bc humidty not detected.");
    digitalWrite(tiny, HIGH);
    blinker = smol;
    Blinky();
    break;
     
    case O2_ERROR:   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
    Serial.println("Apparently no oxygen found so idk how you are alive rn");
    digitalWrite(tiny, LOW);
    blinker = smol;
    Blinky();
    break;
      
    default:
    Serial.println("lets go!");
    digitalWrite(tiny, LOW);
    digitalWrite(smol, LOW);
  }
}  
    

void Blinky() {
  unsigned long currentMillis;
  
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - beginMillis >= period)  //test whether the period has elapsed
  {
    digitalWrite(blinker, !digitalRead(blinker));  //if so, change the state of the LED.  Uses a neat trick to change the state
    beginMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  } 
}
 
