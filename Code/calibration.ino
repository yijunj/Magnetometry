#include <stdio.h>
#include <stdlib.h>
#include <EEPROM.h>
#include <SPI.h>
#include <SD.h>

#define CHIP_SELECT 10
#define EOT 4

File dataFile;

// Serial talks to the magnetometer, irSerial talks to the ir transceiver
void setup() {
  Serial.begin(9600);

  // Create a new timestamped file
  while (!SD.begin(CHIP_SELECT));
  char fileName[10];
  unsigned short recordNum;
  EEPROM.get(0, recordNum);
  sprintf(fileName, "mag%05u.csv", recordNum);
  dataFile = SD.open(fileName, FILE_WRITE);
  while (!dataFile);
  recordNum++;
  EEPROM.put(0, recordNum);

  // Wait for dataFile
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  while(true) {
    // Ask for the magnetic field
    Serial.write("0sd\r");

    while (!Serial.available());
    String magOutput = Serial.readStringUntil(EOT);
    dataFile.println(magOutput);
    
    dataFile.flush();
    delay(100);
  }
}
