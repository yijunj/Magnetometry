#include <stdio.h>
#include <stdlib.h>
#include <SoftwareSerial.h>

#define RX 2
#define TX 3
#define EOT 4

String magOutput = "";
String magSubstring = "";
String mx = "";
String my = "";
String mz = "";
int mxStart = 0;
int mxEnd = 0;
int myStart = 0;
int myEnd = 0;
int mzStart = 0;
int mzEnd = 0;

float mxBias = 0; //38.191;
float myBias = 0; //-7.360;
float mzBias = 0; //7.005;

SoftwareSerial magSerial(RX, TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  magSerial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  magSerial.write("0sd\r");
  while (!magSerial.available());
  magOutput = magSerial.readStringUntil(EOT);
  
  mxStart = magOutput.indexOf(':') + 1;
  magSubstring = magOutput.substring(mxStart);
  mxEnd = magSubstring.indexOf('\r');
  mx = magSubstring.substring(0, mxEnd);
  
  myStart = magSubstring.indexOf(':') + 1;
  magSubstring = magSubstring.substring(myStart);
  myEnd = magSubstring.indexOf('\r');
  my = magSubstring.substring(0, myEnd);

  mzStart = magSubstring.indexOf(':') + 1;
  magSubstring = magSubstring.substring(mzStart);
  mzEnd = magSubstring.indexOf('\r');
  mz = magSubstring.substring(0, mzEnd);
  
  //Serial.println(magOutput);
   
  for (int i=0;i<1;i++) {
//    Serial.print(-39); // To freeze the lower limit
//    Serial.print(" ");
//    Serial.print(-37); // To freeze the upper limit
//    Serial.print(" ");
    Serial.print(millis());
    Serial.print(" ");
    Serial.print(mx.toFloat()*1000-mxBias);
    Serial.print(" ");
    Serial.print(my.toFloat()*1000-myBias);
    Serial.print(" ");
    Serial.print(mz.toFloat()*1000-mzBias);
    Serial.print("\n");
  }
  // Serial.print(magOutput);
  delay(1);
}
