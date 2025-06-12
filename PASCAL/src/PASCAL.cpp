

// All the includes 
#include "Config.h"
#include "Data.h"
#include "components/Logger.h"
#include "components/GPS.h"
#include "components/PumpController.h"
#include "components/Humidity.h"
#include "components/BMP.h"
#include "components/Oxygen.h"
#include "components/Nitrogen.h"


// Defining global variables
Config config;
Data data;
Logger logger = Logger("PASCAL");
GPS gps = GPS();
PumpController controller = PumpController();
HumiditySensor humidity = HumiditySensor();
BMP bmp = BMP();
OxygenSensor oxygen = OxygenSensor();
NO2Sensor no2 = NO2Sensor(config.pins.WE1Pin, config.pins.Aux1Pin, config.pins.PTPin);


// Sets the needed pins to be output or input
void initPins() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(config.pins.exhaustPin, OUTPUT);
	pinMode(config.pins.pumpPin, OUTPUT);
	pinMode(config.pins.brightLEDS, OUTPUT);
	pinMode(config.pins.tiny, OUTPUT);
	pinMode(config.pins.smol, OUTPUT);
	pinMode(config.pins.blinker, OUTPUT);
	pinMode(config.pins.WE1Pin, OUTPUT);
	pinMode(config.pins.Aux1Pin, OUTPUT);
	pinMode(config.pins.PTPin, OUTPUT);
	pinMode(config.pins.i2c.scl, OUTPUT);
	pinMode(config.pins.i2c.sda, OUTPUT);

	// Inits all solenoids, change the upper limit if adding more solenoids
	for (int i = 0; i < 6; i++) {
		pinMode(config.pins.solenoidPins[i], OUTPUT);
	}

	Wire.setSDA(12);
	Wire.setSCL(13);
	Wire.begin();

}

void initComponents() {
	logger.init();
	gps.init();
	humidity.turnOn();
	bmp.init();
	oxygen.init();
	no2.init(config.WEOffset, config.AuxOffset, config.sensitivity, config.temperatureMultiplier);
	controller.init();
}

void collectData() {
	gps.updateData();
	bmp.updateData();
	humidity.updateData();
	no2.updateData();
	oxygen.updateData();
}

void updateState() {

	// TODO update this and use a timer 

	// if ((data.missionTime > thirtyTimer) && (data.state == INITIALIZATION)) // No timer yet so removing it for testing + not needed for this flight
    // {
    //     data.state = STANDBY;
    
    // }
    // else if ((altitude > 500) && (data.state == STANDBY))
    // {
    //     data.state = PASSIVE;
      	
    // }
    // else if ((isItDescending()) && (data.state == PASSIVE))
    // {
    //     data.state = DESCENT;
      
      
    // }
    // else if ((isConstantAlt()) && (data.state == DESCENT) && altitude < 500){
    
    //     data.state = LANDED;
  
    // }

    // oldAlt = altitude;
}


void initLEDs() {
	// TODO
}

void blinky() {
	unsigned long currentMillis;
	currentMillis = millis(); 
   
		// TODO Replace this with a timer
	//   if (currentMillis - beginMillis >= period)  //test whether the period has elapsed
	//   {
	//     digitalWrite(config.pins.blinker, !digitalRead(config.pins.blinker));
	//     if (data.state != INITIALIZATION){
	//       digitalWrite(config.pins.brightLEDS, !digitalRead(config.pins.brightLEDS));  // blinking likes go blink
	//        Serial.println("NORMAL");
	//     }  
	//     beginMillis = currentMillis;  //save the start time of the current LED state.
	//   } 
}

// Checks to see if the payload has been descending for 30 seconds 
bool isItDescending() {

	// TODO update this to use a timer in config

    // if (altitude  < oldAlt) {

    //     velocityInterval++;
    //     Serial.println("going down?!!!!");

    //     if (velocityInterval > 3) // If it descends for over a minute it changes the state to Descending
    //     {
    //         velocityInterval = 0; 
    //         Serial.println("HEY IT SHOULD BE TRUE FOR NEGATIVE VELOCITY!");
    //         return true;
    //     }
    // }
    // else
    // {
    //     velocityInterval = 0;
    //     return false;
    // }
    return false;
}



bool isLanded() {


	// TODO update this in general

	// if ((altitude  < oldAlt + 20) && (altitude  > oldAlt - 20)) /*Checks if payload stationary*/ {
	// 		rangeInterval++;
	// 		if (rangeInterval > 3) // If it stays within +-50 Meters for over a minute it changes the state to Landed
	// 		{
	// 			rangeInterval = 0; 
	// 			return true;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		rangeInterval = 0;
	// 		return false;
	// 	}

	return false;
}
  

// Needs to be updated as the errors are now in the telementry
// This should just show the error codes on the LEDs
// // Function to check for errors and display error codes
// void checkErrors(Error error) {

// TODO update this function to use the leds and a timer in config


// switch(error){		
//     case SD_ERROR:  //error 1 will be SD (all on)
//       config.pins.blinker = LED_BUILTIN; 
//         //digitalWrite(config.pins.tiny, HIGH);
//         //digitalWrite(config.pins.smol, HIGH);
//         config.pins.blinker = LED_BUILTIN;   //IF SD ERROR PICO LED BLINKS
//         break;
    
//     case GPS_ERROR:  //error 2 is GPS (1 on/off)
//         logger.write("Hey, your GPS is messed up!");
//         //digitalWrite(config.pins.tiny, HIGH);
//         //digitalWrite(config.pins.smol, LOW);
//         break;
    
//     case BMP_ERROR:   //BMP (other on/off)
//         logger.write("BMP not found.");
//         //digitalWrite(config.pins.tiny, LOW);
//         //digitalWrite(config.pins.smol, HIGH);
//         break;
    
//     case NO2_ERROR:  // NO2 (tiny blinks and smol on)
//         logger.write("NO2 (the problem child) is not functioning");
//         //digitalWrite(config.pins.smol, HIGH);
//         //config.pins.blinker = config.pins.tiny;
//         // Blinky();
//         break;
    
//     case HUMID_ERROR:  //Humidity (smol blinks and tiny on)
//         logger.write("Must be too dry bc humidity not detected.");
//         //digitalWrite(config.pins.tiny, HIGH);
//         //config.pins.blinker = config.pins.smol;
//         // Blinky();
//         break;
     
//     case O2_ERROR:   //O2 (tiny on and smol blinks) !!!!DIFFERENT FROM WHAT WAS DISCUSSED!!!!
//         logger.write("Apparently no oxygen found so idk how you are alive rn");
//         //digitalWrite(config.pins.tiny, LOW);
//         //config.pins.blinker = config.pins.smol;
//         // Blinky();
//         break;
      
//     default:
//         //sd.write("lets go!");
//         //digitalWrite(config.pins.tiny, LOW);
//         //digitalWrite(config.pins.smol, LOW);
//         digitalWrite(LED_BUILTIN, LOW);
//   }


// }









// Function to get a string representations of the errors for printing
String getErrorString(Error error) {
	switch (error) {
		case SD_ERROR:
			if (error == SD_ERROR) {
				return "SD Error";
			}
		case GPS_ERROR:
			if (error == GPS_ERROR) {
				return "GPS error";
			}
		case BMP_ERROR:
			if (error == BMP_ERROR) {
				return "BMP Error"; 
			}
		case NO2_ERROR:
			if (error == NO2_ERROR) {
				return "Nitrogen Sensor Error";
			}
		case HUMID_ERROR:
			if (error == HUMID_ERROR) {
				return "Humidity Sensor Error";
			}
		case O2_ERROR:
			if (error == O2_ERROR) {
				return "Oxygen Sensor Error";
			}
		default:
			return "No Error";
	}	
}

// Function to get the sample state represented as a string for easy printing
String getSampleStateString(SampleState state) {

	String sampleStateStrs[] = {
		"Sample Not Active",
		"Sample Active",
		"Cleaning",
		"Sealing Sample",
		"Sample Not Active"
	};

	return sampleStateStrs[(int)state];
}

// Function to get the flight state represented as a string for easy printing
String getFlightStateString(FlightState state) {

	String flightStateStrs[] = {
		"Initialization",
		"Standby",
		"Passive",
		"Descending",
		"Landed"
	};

	return flightStateStrs[(int)state];
}

// woah a function that actually puts all the data in a massive string
void logData() { //future reference: nitrogen, Aux, WE
	data.missionTime = millis() / 1000.00;
    
	String Data = config.payload + ", " + 
	getFlightStateString(data.state) + ", " + 
	getSampleStateString(data.sampleState) + ", " +
	String(data.packetNumber) + ", " + 
	String(data.missionTime) + ", " + 
	String(data.gpsData.SIV) + ", " + 
	String(data.gpsData.time.year) + ":" + String(data.gpsData.time.month) + ":" + String(data.gpsData.time.day) + ":" + 
	String(data.gpsData.time.hour) + ":" + String(data.gpsData.time.minute) + ":" + String(data.gpsData.time.second) + ", " + 
	String() + ", " + 
	String(data.atmoData.temperature) + ", " + 
	String(data.atmoData.humidity) + ", " + 

	// TODO Add in the temperature from the humidity sensor

	String(data.atmoData.pressure) + ", " + 
	String(data.gpsData.pos.alt) + ", " + 
	String(data.gpsData.pos.lat) + ", " + 
	String(data.gpsData.pos.lon) +
	getErrorString(data.error);
	
	logger.write(Data);
  
	data.packetNumber++;

}
  

