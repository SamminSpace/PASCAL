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
    int brightsLEDS = 11; 
    int tiny = 7;
    int smol = 8;

    /******************************************There be problems with DEFORESTATION LAWS***********************************/
    GPS gps;
    BMPandHumidity tempAlt;
    NO2 no2;
    SD logger;
    O2 oxygen;
};

// The sensors themselves
struct GPS
{
    int SDA = 26;
    int SCL = 27;
};
struct BMPHumidityAndO2
{
    int SDA = 12;
    int SCL = 13;
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

struct SD
{
    int MISO = 16;
    int MOSI = 19;
    int CS = 17;
    int CLK = 18;

};

struct O2
{
    int SDA = 14;
    int SCL = 15;
};
