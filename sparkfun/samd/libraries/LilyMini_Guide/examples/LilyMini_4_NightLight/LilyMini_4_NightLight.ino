/*
LilyPad LilyMini ProtoSnap Activity 8: Night-Light with Light Sensor
SparkFun Electronics
https://www.sparkfun.com/products/14063

Read the ambient light levels from the LilyPad Light Sensor attached to sew tab 1.
Turn on the LEDs on sew tabs 3 and 4 when the light level falls below a certain level.
Also print the light level to the serial monitor window.

This example is based on: If Statement by Tom Igoe
http://www.arduino.cc/en/Tutorial/IfStatement

This example code is in the public domain

******************************************************************************/

// Declare the variables we'll be using

int sensorPin = 1;    // Input pin for the light sensor
int ledPin1 = 3;      // Output pins for the LEDs
int ledPin2 = 4;
int sensorValue;      // Light level      
int threshold = 100;  // On/off threshold, below this is "dark", above this is "light"

void setup() {

  // Make the sensorPin an INPUT:

  pinMode(sensorPin, INPUT);

  // Make the LED pins outputs:
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Begin serial communications at 9600 bits per second:

  Serial.begin(9600);
}

void loop() {
  
  // Read the analog value (0 to 1023) from the light sensor:

  sensorValue = analogRead(sensorPin);

  // Print out the value to the serial monitor window
  // (Click the magnifying glass icon to open it)
  
  Serial.print("Light sensor value = ");
  Serial.print(sensorValue);
  Serial.print("  ");
  
  // If the analog value is less than the light/dark threshold, turn ON the LEDs,
  // otherwise turn them off. Also print out what we decided:

  if (sensorValue < threshold) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    Serial.println("dark");
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    Serial.println("bright");
  }
}
