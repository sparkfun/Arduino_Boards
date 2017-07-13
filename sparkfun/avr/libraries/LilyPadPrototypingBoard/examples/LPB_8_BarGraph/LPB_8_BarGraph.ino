/*
LilyPad Prototyping Board Activity 8: Bar Graph
SparkFun Electronics
https://www.sparkfun.com/products/14346

Drives the "bar graph" from the light sensor input.
Also provides a bonus "Theremin" from the buzzer (only when the switch is on).

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

// Set up variables for all the pins we're using:

int sensorPin = 2;
int brightness;

int barGraph1 = 15;
int barGraph2 = 16;
int barGraph3 = 17;
int barGraph4 = 18;
int barGraph5 = 19;
int barGraph6 = 20;

int buzzer = 3;
int mySwitch = 9; 

int segmentValue = 100; // analog range for each LED in the bargraph

void setup()
{
  // start the serial connection
  Serial.begin(9600);

  // configure ledPin as an output
  pinMode(barGraph1, OUTPUT);
  pinMode(barGraph2, OUTPUT);
  pinMode(barGraph3, OUTPUT);
  pinMode(barGraph4, OUTPUT);
  pinMode(barGraph5, OUTPUT);
  pinMode(barGraph6, OUTPUT);

  pinMode(mySwitch, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  brightness = analogRead(sensorPin);
  
  // print out the current brightness to the serial monitor
  Serial.println(brightness);

  // Drive the bargraph LEDs:

  if (brightness > (segmentValue * 6)) digitalWrite(barGraph6,HIGH); else digitalWrite(barGraph6,LOW);
  if (brightness > (segmentValue * 5)) digitalWrite(barGraph5,HIGH); else digitalWrite(barGraph5,LOW);
  if (brightness > (segmentValue * 4)) digitalWrite(barGraph4,HIGH); else digitalWrite(barGraph4,LOW);
  if (brightness > (segmentValue * 3)) digitalWrite(barGraph3,HIGH); else digitalWrite(barGraph3,LOW);
  if (brightness > (segmentValue * 2)) digitalWrite(barGraph2,HIGH); else digitalWrite(barGraph2,LOW);
  if (brightness > (segmentValue * 1)) digitalWrite(barGraph1,HIGH); else digitalWrite(barGraph1,LOW);

  // Bonus Theremin feature! (Only if the switch is on)

  if (digitalRead(mySwitch) == LOW)
    tone(buzzer,brightness);
  else
    noTone(buzzer);

  delay(10);
}

