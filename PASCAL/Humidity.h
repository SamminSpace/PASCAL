
class HumiditySensor {
private:

    Adafruit_HDC302x hdc = Adafruit_HDC302x(); //IDK IF RIGHT

    double temp; //temperature dont by humidity
    double RH; // humdity 

public:

    // Initializes the oxygen sensor
    void init();

    // Reads from the oxygen sensor
    float getWetness();

};
