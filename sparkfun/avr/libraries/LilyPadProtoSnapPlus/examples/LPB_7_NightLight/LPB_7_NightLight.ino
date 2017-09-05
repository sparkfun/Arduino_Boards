/*
LilyPad ProtoSnap Plus Activity 8: Night-Light with Light Sensor
SparkFun Electronics
https://www.sparkfun.com/products/14346

Read the ambient light levels from the LilyPad Light Sensor attached to sew tab 2.
Turn on the LEDs on sew tabs A5 and 6 when the light level falls below a certain level.
Also print the light level to the serial monitor window.

This example is based on: If Statement by Tom Igoe
http://www.arduino.cc/en/Tutorial/IfStatement

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Declare the variables we'll be using

int sensorPin = 2;    // Input pin for the light sensor
int sensorValue;      // Light level reading
int threshold = 100;  // On/off threshold, below this is "dark", above this is "light"

int ledPin1 = 5;      // Output pins for the LEDs
int ledPin2 = 6;
int ledPin3 = 7;
int ledPin4 = 8;

void setup() {

  // Make the sensorPin an INPUT:

  pinMode(sensorPin, INPUT);

  // Make the LED pins outputs:
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

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
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    Serial.println("dark");
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    Serial.println("bright");
  }
}
