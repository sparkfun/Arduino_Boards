/*
LilyPad ProtoSnap Plus Activity 2: Buttons and Switches
SparkFun Electronics
https://www.sparkfun.com/products/14346

Read a button (digital input) on pin 4
Turn on the LED on pin 5 when pressed, and off when released.
Read a switch (digital input) on pin 9
Turn on the LED on pin 8 when switch is set to ON, and off when OFF

This sketch was written by SparkFun Electronics,
and is based on InputPullupSerial code by Scott Fitzgerald
http://www.arduino.cc/en/Tutorial/InputPullupSerial
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Create integer variables for the pins we're using:

int buttonPin = 4;
int switchPin = 9;
int ledPin1 = 5;
int ledPin2 = 8;

// Create variables to hold switch/button readings:

int buttonState;
int switchState;

void setup() {

  // Configure the switch and button as inputs with pullup resistors:

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);

  // The pullup is a small internal resistor between the sewtab and HIGH voltage.
  // This weakly "pulls up" the input to HIGH if the button is disconnected (not
  // being pressed). This keeps the input from "floating" (randomly reading either
  // HIGH or LOW) when the button is not being pressed.
  
  // Configure both ledPins as outputs:
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  
  // Read the button and switch states (HIGH or LOW) and store them:
  
  buttonState = digitalRead(buttonPin);
  switchState = digitalRead(switchPin);

  // Note that LOW = pressed and HIGH = released, the opposite of what you might expect.
  // This is because the button is attached to ground, which is the LOW voltage level.
  // When you push the button, it's attached to ground, and digitalRead returns LOW.
  // When the button is released, the pullup resistor pulls the signal to HIGH.
  
  // This "if" statement handles the button state (pressed = LOW, released = HIGH)
  
  if (buttonState == LOW) {       // If LOW, the button is pressed
    digitalWrite(ledPin1, HIGH);  // Turn the LEDs on
  } else {                        // Otherwise it's HIGH, or unpressed
    digitalWrite(ledPin1, LOW);   // Turn the LEDs off
  }

  // This "if" statement handles the switch state (switched on = LOW, switched off = HIGH)

    if (switchState == HIGH) {    // If LOW, the switch is on
    digitalWrite(ledPin2, HIGH);  // Turn the LEDs on
  } else {                        // Otherwise it's HIGH, or off
    digitalWrite(ledPin2, LOW);   // Turn the LEDs off
  }
}



