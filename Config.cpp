// This is where all of our configuration stuff goes.
struct Config
{

    float heights[6] = {
        1000.0,
        5000.0
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
    SD logger;
    i2C devices;

// All the i2c devices 
struct i2C
{
    int SDA = 12;
    int SCL = 13;
};


struct SD //should just be default pins
{
    int MISO = 16;
    int MOSI = 19;
    int CS = 17;
    int CLK = 18;
};
