/******************************************************************************
LilyPad Prototyping Board Activity x: Using the LilyPad Buzzer
SparkFun Electronics
https://www.sparkfun.com/products/14346

This example code shows how use a button to trigger sounds
with the LilyPad Buzzer.

This example is based on one in "Sew Electric" by Leah Buechley & Kanjun Qiu
https://www.sparkfun.com/products/12019

This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Pin the buzzer is attached to:

int buzzerPin = 3;

// Pins the button and switch are attached to:

int buttonPin = 4;
int switchPin = 9;

// Variables to store the button and switch state:

int buttonState;
int switchState;

// Set a time in milliseconds for all delays:

int delayTime = 100; 

// Note values:

int C = 1046;
int D = 1175;
int E = 1319;
int F = 1397;
int G = 1568;
int A = 1760;
int B = 1976;
int C1 = 2093;
int D1 = 2349;

void setup()
{
    // Set the buzzer pin as an OUTPUT:

    pinMode(buzzerPin, OUTPUT);

    // Set the button and switch as INPUT_PULLUPs:
    
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(switchPin, INPUT_PULLUP);
}

void loop()
{
  // Read and store the button and switch
  
  buttonState = digitalRead(buttonPin);
  switchState = digitalRead(switchPin);

  // Call a function named playSongUp or playSongDown

  if (buttonState == LOW) // Button is on
  {
    if (switchState == LOW) {  // Switch is on
      playSongUp();
      } else { // Switch is off
      playSongDown();
    }
  } 
  else // Button is off
  {
    noTone(buzzerPin); // Turn off buzzer
  }
  delay(delayTime);
}

void playSongUp() 
{
  tone(buzzerPin, C);
  delay(delayTime);
  tone(buzzerPin, D);
  delay(delayTime);
  tone(buzzerPin, E);
  delay(delayTime);
  tone(buzzerPin, F);
  delay(delayTime);
  tone(buzzerPin, G);
  delay(delayTime);
  tone(buzzerPin, A);
  delay(delayTime);
  tone(buzzerPin, B);
  delay(delayTime);
  tone(buzzerPin, C1);
  delay(delayTime);
  // Use noTone() to shut off the buzzer and delay to create a 'rest'
  noTone(buzzerPin);
  delay(delayTime); 
}

void playSongDown() 
{
  tone(buzzerPin, C1);
  delay(delayTime);
  tone(buzzerPin, B);
  delay(delayTime);
  tone(buzzerPin, A);
  delay(delayTime);
  tone(buzzerPin, G);
  delay(delayTime);
  tone(buzzerPin, F);
  delay(delayTime);
  tone(buzzerPin, E);
  delay(delayTime);
  tone(buzzerPin, D);
  delay(delayTime);
  tone(buzzerPin, C);
  delay(delayTime);
  // Use noTone() to shut off the buzzer and delay to create a 'rest'
  noTone(buzzerPin);
  delay(delayTime); 
}


