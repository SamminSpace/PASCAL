#include <SD.h>
#include <SPI.h>

const int chipSelect = 17;

void setup()
{

  // Open serial communications and wait for port to open:
  Serial.begin(9600);


  Serial.print("Initializing SD card...");

  pinMode(chipSelect, OUTPUT);

  // see if the card is present and can be initialized:
  while (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    delay(1000);
      // This will change later im just lazy
  }
  Serial.println("card initialized.");
}

void loop()
{

  String openingString = " ________  ________  ________  ________  ________  ___          \n|\\   __  \\|\\   __  \\|\\   ____\\|\\   ____\\|\\   __  \\|\\  \\         \n\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\___|\\ \\  \\|\\  \\ \\ \\        \n \\ \\   ____\\ \\   __  \\ \\_____  \\ \\  \\    \\ \\   __  \\ \\  \\       \n  \\ \\  \\___|\\ \\  \\ \\  \\|____|\\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\____  \n   \\ \\__\\    \\ \\__\\ \\__\\____\\_\\  \\ \\_______\\ \\__\\ \\__\\ \\_______\\n    \\|__|     \\|__|\\|__|\\_________\\|_______|\\|__|\\|__|\\|_______|\n                       \\|_________|                             \n                                                                                                                                \n";
  
  // open the file.
  File dataFile = SD.open("PASCALtest.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(openingString);
    dataFile.close();
    Serial.println("it did it");
  } else {
    Serial.println("error opening file");
  }
  delay(1000);
}

