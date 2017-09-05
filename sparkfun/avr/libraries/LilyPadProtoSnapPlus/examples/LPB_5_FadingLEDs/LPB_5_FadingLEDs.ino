/*
LilyPad ProtoSnap Plus Activity 6: Fading LEDs
SparkFun Electronics
https://www.sparkfun.com/products/14346 

This example shows how to fade an LED using a for() loop and 
the analogWrite() function.

This examples uses the LED pairs on pins 6 and A7 of the LilyMini.

This sketch was written by SparkFun Electronics,
and is based on: Fading by David A. Mellis
http://www.arduino.cc/en/Tutorial/Fading
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Define our LED pins:

int ledPin1 = 5;    
int ledPin2 = 6;
int ledPin3 = 7;
int ledPin4 = 8;

void setup() {

  // Set LED pins to output:
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

void loop() {

  // Fade in from min to max in increments of 5 points:
  
  for (int brightness = 0 ; brightness <= 255; brightness += 5) {

    // Sets the value (range from 0 to 255):
    
    analogWrite(ledPin1, brightness);
    analogWrite(ledPin2, brightness);
    analogWrite(ledPin3, brightness);
    analogWrite(ledPin4, brightness);
    
    // Wait for 30 milliseconds to see the dimming effect
    
    delay(30);
  }
  digitalWrite(ledPin2, HIGH);
  delay(100);

  // Fade out from max to min in increments of 5 points:
  
  for (int brightness = 255 ; brightness >= 0; brightness-= 5) {

    // Sets the value (range from 0 to 255):
    
    analogWrite(ledPin1, brightness);
    analogWrite(ledPin2, brightness);
    analogWrite(ledPin3, brightness);
    analogWrite(ledPin4, brightness);
    
    // wait for 30 milliseconds to see the dimming effect:
    
    delay(30);
  }
  digitalWrite(ledPin2, LOW);
  delay(100);
}


