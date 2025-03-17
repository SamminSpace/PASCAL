
class OxygenSensor {
private:

    DFRobot_OxygenSensor oxygen;

    int collectionNumber = 10; // Can be from 1-100

public:

    // Initializes the oxygen sensor
    void init();

    // Reads from the oxygen sensor
    float getOxygen();

}



