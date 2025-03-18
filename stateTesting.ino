int LEDs = 7;
unsigned long lastBlinkTime = 0;
unsigned long interval = 10000; // 10 sec OFF time for LEDS
int onDuration = 100; // 100 ms ON time for LEDs
bool ledOn = false;  //state whether outside LEDs are on/off



int velocityInterval = 0;  
int rangeInterval = 0;
int thirtyTimer = 30000; // 30 minites is 1800 seconds
unsigned long missionTime; 
double realTime; //this is missionTime minus the initialization time used for simulation 

float gpsAlt;
float oldAlt;
float altDiff; //not really used except to display to serial 


enum State 
{
    INITIALIZATION = 0,
  	STANDBY = 1,
    PASSIVE = 2,
    DESCENT = 3,
    LANDED = 4
};

State flightState; //Starts at INITIALZATION



void setup() {
  Serial.begin(9600);
  pinMode(LEDs, OUTPUT);
  
  flightState = INITIALIZATION;
  velocityInterval = 0;
  rangeInterval = 0;
 
}


void loop() {
     // Testing Purposes
  	missionTime = millis();
  
    Serial.print("Alt: ");
    Serial.print(gpsAlt);
    Serial.print(",  Old Alt: ");
    Serial.print(oldAlt);
  	Serial.print(",  Altidude Differnce: ");
    Serial.println(altDiff);

    
    getAlt();
    decideState();
    Serial.println(flightState);
  	LEDblink();

    
    delay(250); //DELETE 
    
}



float getAlt(){
  altDiff = gpsAlt - oldAlt;
  oldAlt = gpsAlt; 
  realTime = (missionTime - thirtyTimer)/ 1000.000;
  
  if (flightState == INITIALIZATION){
    return gpsAlt;
  }
  
  gpsAlt = (-1 * (.25 * realTime - 11) * (.25 * realTime - 11)) + 115;
  
  if (gpsAlt < 20){
 	gpsAlt = 19;  
  	return gpsAlt;
  }
  
  return gpsAlt;
}



bool isItDescending()
{
    if (gpsAlt < oldAlt)
    {
        velocityInterval++;
        Serial.println("going down?!!!!");

        if (velocityInterval > 4) // If it descends for over a minute it changes the state to Descending
        {
            velocityInterval = 0; 
            Serial.println("set vel to zero");
            Serial.println("HEY IT SHOULD BE TRUE FOR NEGATIVE VELOCOTY!");
            return true;
        }
    }
    else
    {
        velocityInterval = 0;
        Serial.println("we got set to zero");
        return false;
    }
    return false;
}



bool isConstantAlt()
{
  if ((gpsAlt < oldAlt + 5) && (gpsAlt > oldAlt - 5)) //Checks if payload stationary
    {
        rangeInterval++;
        if (rangeInterval > 4) // If it stays within +-50 Meters for over a minute it changes the state to Landed
        {
            rangeInterval = 0; 
            return true;
        }
    }
    else
    {
        rangeInterval = 0;
        return false;
    }

    return false;
 }



void decideState() // TODO Run this every 15 seconds
{
  
    if ((missionTime > thirtyTimer) && (flightState == INITIALIZATION))
    {
        flightState = STANDBY;
    
    }
    else if ((gpsAlt > 60) && (flightState == STANDBY))
    {
        flightState = PASSIVE;
      	
    }
    else if ((isItDescending()) && (flightState == PASSIVE))
    {
        flightState = DESCENT;
      
      
    }
    else if ((isConstantAlt()) && (flightState == DESCENT) && gpsAlt < 20)
    {
        flightState = LANDED;
  
    }
}


void LEDblink(){
  if (flightState == INITIALIZATION){   //.LED Blink pattern for initialization
    interval = 10000; // 10 sec OFF time for LEDS
    onDuration = 100; // 100 ms ON time for LEDs
  } 
  else {
    interval = 1500; //Off time for normal blink
    onDuration = 1000;  //On time for normal blink
  }
  
  unsigned long currentMillis = millis();

 	 if (!ledOn && (currentMillis - lastBlinkTime >= interval)) {
   		 digitalWrite(LEDs, HIGH);
   		 ledOn = true;
   		 lastBlinkTime = currentMillis;
 	}		
 		 if (ledOn && (currentMillis - lastBlinkTime >= onDuration)) {
   		 digitalWrite(LEDs, LOW);
   		 ledOn = false;
 	 }
}
