//I think this should work but it needs to be tested - Matthew

int interval = 0;
float gpsAlt;
float oldAlt;

enum State 
{
    INITIALIZATION = 0,
    STANDBY = 1,
    PASSIVE = 2,
    DESCENT = 3,
    LANDED = 4
};

State flightState; //Starts at STANDBY

bool isItDescending()
{
    if (gpsAlt<oldAlt)
    {
        interval++;
        if (interval>4) // If it descends for over a minute it changes the state to Descending
        {
            return true;
        }
    }
    else
    {
        interval = 0;
        return false;
    }
}


bool isConstantAlt()
{
  if ((gpsAlt<oldAlt+50) && (gpsAlt>oldAlt-50)) //Checks if the gpsAlt is within a range of 50 meters from the oldAlt
    {
        interval++;
        if (interval>4) // If it stays within +-50 Meters for over a minute it changes the state to Landed
        {
            return true;
        }
    }
    else
    {
        interval = 0;
        return false;
    }
}


void decideState() // TODO Run this every 15 seconds
{
    if (!stillInitializing && flightState == INITIALIZATION)
    {
        flightState = STANDBY;
    }
    else if ((gpsAlt > 500) && (flightState == STANDBY))
    {
        flightState = PASSIVE;
    }
    else if ((isItDescending()) && (flightState == PASSIVE))
    {
        flightState = DESCENT;
        interval = 0;
    }
    else if ((isConstantAlt()) && (flightState == DESCENT))
    {
        flightState = LANDED;
    }
    oldAlt = gpsAlt; 
}
void setup() {
Serial.begin(9600);

//delay(30*60*1000) // 30 Minutes * 60 Seconds * 1000 Milliseconds   *******************Probably should change this to not a delay*****************************
stillInitializing = true;
}

void loop() {
    /* // Testing Purposes
    gpsAlt = 600;
    decideState();
    Serial.println(flightState);
    */
}
