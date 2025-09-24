#include <SoftwareSerial.h>

#include <Wire.h>
#include <Servo.h>

int servoPin = 13;

Servo servo1;


void setup()
{
  Wire.begin(2);
  Wire.onReceive(changeAngerLevel);

  Serial.begin(115200);
  servo1.attach(servoPin);
}

byte angerLevel = 1;

void changeAngerLevel(int numBytesRead) {
  angerLevel = Wire.read();
}
int pos = 0;
void loop() 
{
  if (pos < 180) {
    pos++;
    servo1.write(pos);
  }
  else {
    pos = 0;
  }

    if (angerLevel == 1) {
      digitalWrite(5, LOW);
      digitalWrite(11, LOW);
  
    }
    else if (angerLevel == 2) {
      digitalWrite(5, LOW);
      digitalWrite(11, LOW);

    }
    else if (angerLevel == 3) {
      digitalWrite(5, LOW);
      digitalWrite(11, LOW);


    }
    else if (angerLevel == 4) {
      digitalWrite(5, HIGH);
      digitalWrite(11, HIGH);
    }
    else if (angerLevel == 5) {
      digitalWrite(5, HIGH);
      digitalWrite(11, HIGH);

    }
  }

