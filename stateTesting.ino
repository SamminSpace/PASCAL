
int velocityInterval = 0;
int rangeInterval = 0;
int thirtyTimer = 10; // 30 minites is 1800 seconds
unsigned long missionTime; 
unsigned long realTime; //this is minus the initialization time

float gpsAlt;
float oldAlt;
float altDiff;


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

  flightState = INITIALIZATION;
  velocityInterval = 0;
  rangeInterval = 0;

}


void loop() {
     // Testing Purposes
  	missionTime = millis() / 1000;
  
    Serial.print("Alt: ");
    Serial.print(gpsAlt);
    Serial.print(",  Old Alt: ");
    Serial.print(oldAlt);
  	Serial.print(",  Altidude Differnce: ");
    Serial.println(altDiff);

    
    getAlt();
    decideState();
    Serial.println(flightState);

    
    delay(1000);
    
}



float getAlt(){   //test code for like a 1.5 min test
  altDiff = gpsAlt - oldAlt;
  oldAlt = gpsAlt; 
  realTime = missionTime - thirtyTimer; //the actual time for mock altitude function 

// if in initial state, payload no move
  if (flightState == INITIALIZATION){
    return gpsAlt;
  }

// this is a quadric that mimics balloon flight; need to be changed for long flight
  gpsAlt = (-1 * (.25 * realTime - 11) * (.25 * realTime - 11)) + 115;

// once get under a threshhold, stay constant
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
  if ((gpsAlt<oldAlt+10) && (gpsAlt>oldAlt-10)) //Checks if the gpsAlt is within a range of 50 meters from the oldAlt
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
      	Serial.println("STANDBY");
    }
    else if ((gpsAlt > 60) && (flightState == STANDBY))
    {
        flightState = PASSIVE;
      		Serial.println("PASSIVE");
    }
    else if ((isItDescending()) && (flightState == PASSIVE))
    {
        flightState = DESCENT;
        	Serial.println("DESCENT");
      
    }
    else if ((isConstantAlt()) && (flightState == DESCENT) && gpsAlt < 20) //CHANEG LATER
    {
        flightState = LANDED;
        	Serial.println("LANDED");
    }
   
}
