/*
LilyPad LilyMini ProtoSnap Activity 7: Reading a Light Sensor
SparkFun Electronics
https://www.sparkfun.com/products/14063

Read the ambient light level from the LilyPad Light Sensor attached to sew tab 1.
Blink the LEDs on sew tabs 3 and 4 faster or slower depending on the light level.
Also print the light level to the serial monitor window.

This example is based on: AnalogInput by David Cuartielles
 http://www.arduino.cc/en/Tutorial/AnalogInput

This example code is in the public domain

******************************************************************************/

// Declare the variables we'll be using:

int sensorPin = 1;    // Input pin for the light sensor
int ledPin1 = 3;      // Output pins for the LEDs
int ledPin2 = 4;
int sensorValue = 0;  // Variable to store the light level

void setup() {

  // Set the sensorPin as an INPUT
  
  pinMode(sensorPin, INPUT);  

  // Set the ledPins as OUTPUTs:

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Begin using the serial port:
  
  Serial.begin(9600); // Set the serial port speed to 9600 bits per second
}

void loop() {

  // Read the analog value from the light sensor:
  // This will be a number from 0 (dark) to 1023 (very bright)
  
  sensorValue = analogRead(sensorPin);

  // Print the number we read to the serial monitor window:
  // (Click the magnifying glass icon to open the window)
  
  Serial.print("Light sensor value = ");
  Serial.println(sensorValue);
  
  // Turn the LEDs on:
  
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  
  // Wait for <sensorValue> milliseconds:

  delay(sensorValue);
  
  // turn the LEDs off:
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);

  // Wait for <sensorValue> milliseconds:

  delay(sensorValue);
}
