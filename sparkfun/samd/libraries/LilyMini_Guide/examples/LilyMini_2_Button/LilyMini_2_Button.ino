/*
LilyPad LilyMini ProtoSnap Activity 2: Button
SparkFun Electronics
https://www.sparkfun.com/products/14063

Read a button (digital input) on pin 2
Turn on the LED when pressed, and off when released.

This example is based on InputPullupSerial code by Scott Fitzgerald
http://www.arduino.cc/en/Tutorial/InputPullupSerial

This example code is in the public domain

******************************************************************************/

// Create integer variables for the pins we're using:

int buttonPin = 2;
int ledPin1 = 3;
int ledPin2 = 4;

// Create a variable called "buttonState" to hold button readings:

int buttonState;

void setup() {

  // Configure buttonPin as an input, and enable the internal "pullup resistor":

  pinMode(buttonPin, INPUT_PULLUP);

  // The pullup is a small internal resistor between the sewtab and HIGH voltage.
  // This weakly "pulls up" the input to HIGH if the button is not being pressed.
  // This keeps the input from "floating" (randomly reading either HIGH or LOW)
  // when the button is not being pressed.
  
  // Configure both ledPins as outputs:
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  
  // Read the pushbutton state (HIGH or LOW) and store it in the "buttonState" variable:
  
  buttonState = digitalRead(buttonPin);

  // Note that LOW = pressed and HIGH = released, the opposite of what you might expect.
  // This is because the button is attached to ground, which is the LOW voltage level.
  // We use the pullup to weakly "pull up" the button to HIGH when it's not being pressed.
  // When the button is pressed, the strong ground signal overwhelms the weak pullup signal. 

  // Now turn on both ledPins when the button is pressed, and off when it's not:

  if (buttonState == LOW) {       // If LOW, the button is pressed
    digitalWrite(ledPin1, HIGH);  // Turn the LEDs on
    digitalWrite(ledPin2, HIGH);
  } else {                        // Otherwise it's HIGH, or unpressed
    digitalWrite(ledPin1, LOW);   // Turn the LEDs off
    digitalWrite(ledPin2, LOW);
  }

  // The if statement turns the LEDs off (LOW) when the button is not being pressed (HIGH),
  // and on (HIGH) when the button is pressed (LOW).
}



