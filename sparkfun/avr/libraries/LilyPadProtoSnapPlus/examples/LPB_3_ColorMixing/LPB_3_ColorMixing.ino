/*
LilyPad ProtoSnap Plus Activity 3: Color Mixing
SparkFun Electronics
https://www.sparkfun.com/products/14346 

Make an RGB LED display a rainbow of colors!

An RGB LED is actually three LEDs (red, green, and blue) in
one package. When you turn them on and off in various combinations,
the red, green and blue mix to form new colors.

The RGB LED is permanently connected to the following pins:

Red - pin 12
Green - pin 13
Blue - pin 14

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Create and set variables for the RGB LED pins:

int RED_PIN = 12;
int GREEN_PIN = 13;
int BLUE_PIN = 14;

// Set a variable delayTime for the pause between color changes
// This variable controls how fast we loop through the colors.
// (Try changing this to make the colors change faster or slower.)

int delayTime = 1000; // 1000 milliseconds = 1 second

void setup()
{
  // Here we'll configure the LilyMini pins we're using to
  // drive the LED to be outputs:
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop()
{
  // We're going to turn the individual LEDs (red, blue, and green)
  // on and off in various combinations. This gives you a total of
  // eight colors (if you count "black" as a color).
  // Note that we use delay between each color to slow it down so
  // you can see them.
  
  // Black (all LEDs off)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(delayTime);
  
  // Red (turn just the red LED on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(delayTime);
  
  // Green (turn just the green LED on):
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(delayTime);
  
  // Blue (turn just the blue LED on):
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(delayTime);
  
  // Yellow (turn red and green on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(delayTime);
  
  // Cyan (turn green and blue on):
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(delayTime);
  
  // Purple (turn red and blue on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(delayTime);
  
  // White (turn all the LEDs on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(delayTime);
}


