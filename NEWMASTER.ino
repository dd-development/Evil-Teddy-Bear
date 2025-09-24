// Import necessary library for LCD
#include <LiquidCrystal.h>
#include <Wire.h> 

// Pin definitions
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Ultrasonic sensor pins
const int trigPin = 9; //orange
const int echoPin = 10; //red   

const int buttonReset = 7;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
byte angerLevel = 1; 


// Variables for storing duration and distance
float echoDuration, distance;
int distancePast = 1;
int bearNow = 1; 

void updateAngerLevel(int level) {
    // while sitting
    
    if (level < 5) {
      angerLevel++;
    }
      
    Wire.beginTransmission(1);
    Wire.write(level);
    Wire.endTransmission();
    Wire.beginTransmission(2);
    Wire.write(level);
    Wire.endTransmission();  
    Wire.beginTransmission(3);
    Wire.write(level);
    Wire.endTransmission();   
}


void setup() {
   // Set the trigger and echo pins
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(buttonReset, INPUT); 
   // Begin serial communication
   Serial.begin(9600);
   
   lcd.begin(16, 2);
   Wire.begin(0x0B);
      // Initialize LCD display with 16 columns and 2 rows
}
  
void loop() {

  // Set the cursor position on the LCD to the beginning of the second line
   lcd.setCursor(0, 1);
   digitalWrite(LED_BUILTIN, HIGH);
  
   int buttonState = digitalRead(buttonReset);
   // Print the current time in seconds on the LCD
   lcd.print(millis() / 1000);
  
   // Send a pulse on the trigPin
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
  
   // Measure the echo duration in microseconds
   echoDuration = pulseIn(echoPin, HIGH);
  
   // Calculate the distance based on the echo duration
   distance = (echoDuration * 0.0343) / 2;
  
   // Print the distance on the serial monitor
  //  Serial.print("Distance: ");
  //  Serial.println(distance);
   if (buttonState == HIGH){
    angerLevel = 0 ;
    Wire.beginTransmission(1);
    Wire.write(angerLevel);
    Wire.endTransmission();
    Wire.beginTransmission(2);
    Wire.write(angerLevel);
    Wire.endTransmission();  
    Wire.beginTransmission(3);
    Wire.write(angerLevel);
    Wire.endTransmission();   
   }
   // Display the distance on the LCD on the second line
   lcd.setCursor(0, 1);
   lcd.print("Distance: ");
   lcd.print(distance);
   lcd.print(" cm");

   if ( distance < 15 ) { 
    bearNow = 1; 
   }
   else { 
    bearNow = 0;
   }

   if (distancePast != bearNow ) {
        if ( distancePast ==  0 && bearNow == 1){
        updateAngerLevel(angerLevel);
        } 
        distancePast = bearNow; 
        Serial.print(angerLevel);

    }

}



