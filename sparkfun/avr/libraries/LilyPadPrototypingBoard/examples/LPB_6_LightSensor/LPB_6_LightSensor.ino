/*
LilyPad ProtoSnap Plus Activity 7: Reading a Light Sensor
SparkFun Electronics
https://www.sparkfun.com/products/14346

Read the ambient light level from the LilyPad Light Sensor attached to sew tab 1.
Blink the LEDs on sew tabs 3 and 4 faster or slower depending on the light level.
Also print the light level to the serial monitor window.

This example is based on: AnalogInput by David Cuartielles
 http://www.arduino.cc/en/Tutorial/AnalogInput

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Create variables for the pins we'll be using:

int sensorPin = 2;    // Input pin for the light sensor
int sensorValue = 0;  // Variable to store the light level

int ledPin1 = 5;      // Output pins for the LEDs
int ledPin2 = 6;
int ledPin3 = 7;
int ledPin4 = 8;

void setup() {

  // Set the sensorPin as an INPUT:
  
  pinMode(sensorPin, INPUT);  

  // Set the ledPins as OUTPUTs:

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

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
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  
  // Wait for <sensorValue> milliseconds:

  delay(sensorValue);
  
  // turn the LEDs off:
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);

  // Wait for <sensorValue> milliseconds:

  delay(sensorValue);
}
