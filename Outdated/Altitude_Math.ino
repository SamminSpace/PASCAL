float targetAltitude = 7000;
float maxStorm = 13000; //the top of the storm
float minStorm = 2000; //bottom of storm 
float array[6] = {1000, 6000, 7000, 7200, 8000, 20000};

void setup() {
   Serial.begin(9600);
   getAltitideSample();
}

void loop() {
  // put your main code here, to run repeatedly:

}


void getAltitideSample() //Sets the altitudes we will be sampling at
{
  array[0] = 1000; //1st sample before the storm
  Serial.println(array[0]);

  array[1] = targetAltitude - 2000; //2nd sample is 2km below target
  Serial.println(array[1]);

  array[2] = targetAltitude; //3rd sample is target
  Serial.println(array[2]);

  array[3] = targetAltitude + 500; //4th sample is just above target
  Serial.println(array[3]);

  array[4] = targetAltitude + 2000; //5th sample is 2km above target
  Serial.println(array[4]);

  array[5] = 20000;     //6th sample after storm near apogee
  Serial.println(array[5]);
}
