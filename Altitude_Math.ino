float targetOne = 5000;
float targetTwo = 9000;
float array[4] = {1000, 5000, 9000, 20000};

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

  array[1] = targetOne //2nd and 3rd sample in negavtive storm area
  Serial.println(array[1]);

  array[2] = targetTwo; //4th and 5th sample in postive storm area
  Serial.println(array[2]);

  array[3] = 20000 //6thh sample is at apogee
  Serial.println(array[3]);
}
