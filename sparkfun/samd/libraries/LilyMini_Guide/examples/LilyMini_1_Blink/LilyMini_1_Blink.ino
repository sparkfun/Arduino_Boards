/*
LilyPad LilyMini ProtoSnap Activity 1: Blink
SparkFun Electronics
https://www.sparkfun.com/products/14063

Turns on an LED attached to the LilyMini's sew tab 3 on for one second, then off 
for one second, forever.

This example is based on: Blink by Scott Fitzgerald
https://www.arduino.cc/en/Tutorial/Blink

This example code is in the public domain

******************************************************************************/

// The setup function runs once when the LilyMini turns on:

void setup() {
  pinMode(3, OUTPUT);     // Initialize pin 3 as a digital output:
}

// Once the setup function runs, the loop function runs over and over:

void loop() {
  digitalWrite(3, HIGH);   // Give pin 3 a HIGH voltage level (on), which lights up the LED
  delay(1000);             // Wait for one second (the LED stays on)
  digitalWrite(3, LOW);    // Give pin 3 a LOW voltage level (off), which turns off the LED
  delay(1000);             // Wait for one second (the LED stays off)
}
