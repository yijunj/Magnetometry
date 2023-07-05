#include <stdio.h>
#include <stdlib.h>
#include <EEPROM.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

#define CHIP_SELECT 10
#define RXIR 2
#define TXIR 3
#define EOT 4
#define ACCX A4
#define ACCY A5
#define ACCZ A6

int accx0 = 326;
int accy0 = 328;
int accz0 = 337;
float gx = 37.0;
float gy = 67.0;
float gz = 67.0;

SoftwareSerial irSerial(RXIR, TXIR); // RX, TX
File dataFile;

// Serial talks to the magnetometer, irSerial talks to the ir transceiver
void setup() {
  Serial.begin(9600);
  irSerial.begin(9600);

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
  if(irSerial.available()) {
    // If ir receives a position, ask for the magnetic field
    Serial.write("0sd\r");
    
    String posOutput = irSerial.readStringUntil('\n');
    String posOutputTrim = posOutput.substring(posOutput.length()-4);
    dataFile.print("X:");
    dataFile.println(posOutputTrim);

    int accx = analogRead(ACCX);
    int accy = analogRead(ACCY);
    int accz = analogRead(ACCZ);
    dataFile.print("AX:");
    dataFile.println((accx-accx0)/gx, 3);
    dataFile.print("AY:");
    dataFile.println((accy-accy0)/gy, 3);
    dataFile.print("AZ:");
    dataFile.println((accz-accz0)/gz, 3);

    while (!Serial.available());
    String magOutput = Serial.readStringUntil(EOT);
    dataFile.println(magOutput);
    
    dataFile.flush();
    delay(10);
  }
}
