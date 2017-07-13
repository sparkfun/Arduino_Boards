/*
LilyPad Prototyping Board Activity 1: Blink
SparkFun Electronics
https://www.sparkfun.com/products/14346

Turns on the LEDs attached to the LilyPad Prototyping Board's sew tab 6 on for one 
second,then off for one second, forever.

This sketch was written by SparkFun Electronics,
and is based on Blink by Scott Fitzgerald
https://www.arduino.cc/en/Tutorial/Blink
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// The setup function runs once when the LilyMini turns on:

void setup() {
  pinMode(6, OUTPUT);     // Initialize pin 6 as a digital output:
}

// Once the setup function runs, the loop function runs over and over:

void loop() {
  digitalWrite(6, HIGH);   // Give pin 6 a HIGH voltage level (on), which lights up the LED
  delay(1000);             // Wait for one second (the LED stays on)
  digitalWrite(6, LOW);    // Give pin 6 a LOW voltage level (off), which turns off the LED
  delay(1000);             // Wait for one second (the LED stays off)
}
