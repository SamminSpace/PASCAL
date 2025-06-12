
#include <Adafruit_BMP3XX.h>
#include "PASCAL.h"

class BMP {


public:
    Adafruit_BMP3XX bmp;

    // Initializes the BMP 
    void init();

    // Reads from the BMP and the reading
    void updateAltitude();
    void updatePressure();
    void updateTemperature();

	// Refreshes each of the datapoints
	void updateData();

};
