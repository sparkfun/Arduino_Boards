/*
LilyPad Prototyping Board Activity 5: Incrementing Brightness
SparkFun Electronics
https://www.sparkfun.com/products/14346

Read a button (digital input) on pin A4. Whenever the button is pressed,
increment the brightness of a LED. After the LED is at maximum brightness,
start over.

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Pin numbers; the button is on pin A4, the LEDs are on pins 5 through 8

int buttonPin = 4;
int ledPin1 = 5;
int ledPin2 = 6;
int ledPin3 = 7;
int ledPin4 = 8;

// Start the LED brightness at 0 (off)

int brightness = 0;

void setup()
{
  // Configure buttonPin as an input and enable the internal pull-up resistor

  pinMode(buttonPin, INPUT_PULLUP);

  // Configure the ledPins as an output

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  // print out the current brightness to the serial monitor
  Serial.println(brightness);
}

void loop()
{
  // Wait for a button press
  // The button will read as LOW when it's pressed

  if (digitalRead(buttonPin) == LOW)
  {
    // The button has been pressed!
    // Let's make the LED brighter
    
    // Add 1 to the LED brightness variable
    // brightness++ is a shortcut for brightness = brightness + 1

    brightness++;

    // analogWrite() only supports numbers from 0 to 255
    // If brightness is greater than 255, reset it to 0
    
    if (brightness > 255)
    {
      brightness = 0;
    }

    // Set the LEDs to the requested brightness.
    // Note that analogWrite() only works with pins with the "~" symbol.
    // Pin 5 (ledPin1) doesn't have this symbol, so it will blink on and off
    // instead of brightening.
    
    analogWrite(ledPin1,brightness);
    analogWrite(ledPin2,brightness);
    analogWrite(ledPin3,brightness);
    analogWrite(ledPin4,brightness);

    // Slow down a little bit so brightness doesn't change too quickly

    delay(10);
  }
}

