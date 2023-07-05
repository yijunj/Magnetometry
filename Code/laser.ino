#include <SoftwareSerial.h>
SoftwareSerial irSerial(2, 3);
char buff[4] = {0x80, 0x06, 0x03, 0x77};
unsigned char data[11] = {0};

void(* resetFunc) (void) = 0; //declare reset function at address 0

void setup()
{
 Serial.begin(9600);
 irSerial.begin(9600);
}

void loop()
{
  Serial.print(buff);
  while(true)
  {
    if(Serial.available() > 0) // Determine whether there is data to read on the serial 
    {
      for(int i=0; i<11; i++)
      {
        data[i] = Serial.read();
      }
      unsigned char Check = 0;
      for(int i=0; i<10; i++)
      {
        Check = Check + data[i];
      }
      Check = ~Check + 1;
      if(data[10] == Check)
      {
        if(data[3] != 'E' || data[4] != 'R' || data[5] != 'R')
        {
          char buffer[5];
          if(data[0] < '0' || data[0] > '9')
          {
            data[0] = '0';
          }
          if(data[1] < '0' || data[1] > '9')
          {
            data[1] = '0';
          }
          if(data[2] < '0' || data[2] > '9')
          {
            data[2] = '0';
          }
          sprintf(buffer, "%04d\n", int(atof(data)*1000));
          irSerial.write(buffer);
        }
      }
    }
    delay(100);
  }
}
