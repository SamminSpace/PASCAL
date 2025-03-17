//I think this should work but it needs to be tested - Matthew

int interval = 0;
float gpsAlt;
float oldAlt;

enum State 
{
    STANDBY = 0,
    PASSIVE = 1,
    DESCENT = 2,
    LANDED = 3
};

State flightState; //Starts at STANDBY

bool isItDescending()
{
    if (gpsAlt < oldAlt)
    {
        interval++;
        Serial.println("HEY YES ONNCE!!!!");

        if (interval > 4) // If it descends for over a minute it changes the state to Descending
        {
            interval = 0; 
            Serial.println("we set to zero");
            Serial.println("HEY IT SHOULD BE TRUE FOR NEGATIVE VELOCOTY!");
            return true;
        }
    }
    else
    {
        interval = 0;
        Serial.println("we set to zero");
        return false;
    }
    return false;
}



bool isConstantAlt()
{
  if ((gpsAlt<oldAlt+7) && (gpsAlt>oldAlt-7)) //Checks if the gpsAlt is within a range of 50 meters from the oldAlt
    {
        interval++;
        if (interval > 3) // If it stays within +-50 Meters for over a minute it changes the state to Landed
        {
            interval = 0; 
            return true;
        }
    }
    else
    {
        interval = 0;
        return false;
    }

    return false;
 }
}


void decideState() // TODO Run this every 15 seconds
{
    if ((gpsAlt > 500) && (flightState == STANDBY))
    {
        flightState = PASSIVE;
    }
    else if ((isItDescending()) && (flightState == PASSIVE))
    {
        flightState = DESCENT;
        interval = 0;
    }
    else if ((isConstantAlt()) && (flightState == DESCENT) && gpsAlt < 1500)
    {
        flightState = LANDED;
    }
   
}
void setup() {
  Serial.begin(9600);
  flightState = PASSIVE;
  interval = 0;


}

void loop() {
     // Testing Purposes
    Serial.print("Alt: ");
    Serial.println(gpsAlt);
    Serial.print("Old Alt: ");
    Serial.println(oldAlt);

    
    getAlt();
    decideState();
    Serial.println(flightState);

    delay(250);
    
}



int getAlt(){

  oldAlt = gpsAlt; 
  gpsAlt = 18000 + (200 * millis() / 1000) - (6 * millis() * millis () / 1000 / 1000 );

  if (gpsAlt < 17000){
    gpsAlt = 16000;
    return gpsAlt;
  }
 
  return gpsAlt;



}
