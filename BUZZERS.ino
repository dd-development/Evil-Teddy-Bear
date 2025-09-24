#include <SoftwareSerial.h>

#include <Wire.h>
const int vibration = 9; 

void setup()
{
  Wire.begin(3);
  Wire.onReceive(changeAngerLevel);
  Serial.begin(115200);
  pinMode(9,OUTPUT);

}

byte angerLevel = 1;

void changeAngerLevel(int numBytesRead) {
  angerLevel = Wire.read();
}

void loop() 
{

    if (angerLevel == 1) {
      digitalWrite(9, LOW);
    }
    else if (angerLevel == 2) {
      digitalWrite(9, LOW);

    }
    else if (angerLevel == 3) {
      digitalWrite(9, LOW);


    }
    else if (angerLevel == 4) {
      digitalWrite(9, HIGH);


    }
    else if (angerLevel == 5) {
      digitalWrite(9, HIGH);

    }
  }

