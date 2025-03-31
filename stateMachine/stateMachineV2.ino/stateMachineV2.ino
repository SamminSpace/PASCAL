//I think this should work but it needs to be tested - Matthew

int interval = 0;
bool collectingAir = false;
float gpsAlt;
float oldAlt;


enum State 
{
    STANDBY = 0,
    PASSIVE = 1,
    DESCENT = 2,
    LANDED = 3
};

enum SampleState
{
    INITIALIZING = 0, // Payload is initializing or is below first collection
    BEFORE_STORM = 1,
    NEG_TARGET = 2,
    POS_TARGET = 3,
    ABOVE_STORM = 4,
    DONE = 5 // Sampling is done
};

SampleState sampleStatus;

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
    }
    return false;
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
    }
    return false;
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
    else if ((isConstantAlt()) && (flightState == DESCENT))
    {
        flightState = LANDED;
    }
    oldAlt = gpsAlt; 
}

void sampling()
{
    if (gpsAlt>1000 && sampleStatus == 0) // TODO change 1000 to Config.heights[0]
    {
        getSample(0);
    }
    else if (gpsAlt>5000 && sampleStatus == 1) // TODO change 5000 to Config.heights[1]
    {
        getSample(1);
    }
    else if (gpsAlt>9000 && sampleStatus == 2) // TODO change 9000 to Config.heights[2]
    {
        getSample(2);
    }
    else if (gpsAlt>20000 && sampleStatus == 3) // TODO change 20000 to Config.heights[3]
    {
        getSample(3);
    }
}

void getSample(int sampleNum)
{
    // Get that sample
    // We can use Config.solenoidPins[sampleNum] 

}


void setup() {
    Serial.begin(9600);
}

void loop() {
    /* // Testing Purposes
    gpsAlt = 600;
    decideState();
    Serial.println(flightState);
    */
   
}
