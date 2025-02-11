// This is where all of our configuration stuff goes.
struct Config
{

    float heights[6] = {
        1000.0,
        6000.0,
        7000.0,
        8000.0,
        9000.0,
        20000.0}; // m

    // Below here are the pins
    int solenoidPins[6] = {
        2,
        3,
        4,
        5,
        6,
        9};
    int exhaustPin = 10;
    int motorPin = 1;
    int brightsLEDS = 11; // Unconfirmed
    int tiny = 12;
    int smol = 13;

    /******************************************There be problems with DEFORESTATION LAWS***********************************/
    GPS gps;
    BMPHumidityAndO2 daBigOne;
    NO2 no2;
};

// The sensors themselves
struct GPS
{
    int SDA = 16;
    int SCL = 17;
};
struct BMPHumidityAndO2
{
    int SDA = 18;
    int SCL = 19;
};
// This one is hooked up to the ADC here, but eventually it connects to the NO2 sensors
struct NO2
{
    int SDA = 20;
    int SCL = 21;

    // These are the pins for the ADC
    int A0;
    int A1;
    int A2;
    int A3;
};
