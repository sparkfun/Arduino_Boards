// the setup function runs once when you press reset or power the board
#define EXTLED5 5 
#define EXTLED6 6 
#define EXTLED7 7 
#define EXTLED8 8 

#define INTLEDR 12
#define INTLEDG 13
#define INTLEDB 14

#define INTLED0 15
#define INTLED1 16
#define INTLED2 17
#define INTLED3 18
#define INTLED4 19
#define INTLED5 20

#define DELAY_A_MS 5

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(EXTLED5, OUTPUT);
  pinMode(EXTLED6, OUTPUT);
  pinMode(EXTLED7, OUTPUT);
  pinMode(EXTLED8, OUTPUT);
  pinMode(INTLEDR, OUTPUT);
  pinMode(INTLEDG, OUTPUT);
  pinMode(INTLEDB, OUTPUT);
  pinMode(INTLED0, OUTPUT);
  pinMode(INTLED1, OUTPUT);
  pinMode(INTLED2, OUTPUT);
  pinMode(INTLED3, OUTPUT);
  pinMode(INTLED4, OUTPUT);
  pinMode(INTLED5, OUTPUT);

  analogWrite(EXTLED6, 0);
  analogWrite(EXTLED7, 0);
  analogWrite(EXTLED8, 0);
  analogWrite(INTLEDR, 0);
  analogWrite(INTLEDG, 0);
  analogWrite(INTLEDB, 0);

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(INTLED0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(INTLED0, LOW);    // turn the LED off by making the voltage LOW

  digitalWrite(INTLED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(INTLED1, LOW);    // turn the LED off by making the voltage LOW

  digitalWrite(INTLED2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(INTLED2, LOW);    // turn the LED off by making the voltage LOW

  digitalWrite(INTLED3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(INTLED3, LOW);    // turn the LED off by making the voltage LOW

  digitalWrite(INTLED4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(INTLED4, LOW);    // turn the LED off by making the voltage LOW
  
  digitalWrite(INTLED5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(INTLED5, LOW);    // turn the LED off by making the voltage LOW

  digitalWrite(EXTLED5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(EXTLED5, LOW);    // turn the LED off by making the voltage LOW
  
  ///digitalWrite(EXTLED6, HIGH);   // turn the LED on (HIGH is the voltage level)
  ///delay(1000);                       // wait for a second
  ///digitalWrite(EXTLED6, LOW);    // turn the LED off by making the voltage LOW
  for(int i = 0; i < 255; i++)
  {
	  analogWrite(EXTLED6, i);
	  delay(DELAY_A_MS);
  }
  analogWrite(EXTLED6, 0);

  ///digitalWrite(EXTLED7, HIGH);   // turn the LED on (HIGH is the voltage level)
  ///delay(1000);                       // wait for a second
  ///digitalWrite(EXTLED7, LOW);    // turn the LED off by making the voltage LOW
  for(int i = 0; i < 255; i++)
  {
	  analogWrite(EXTLED7, i);
	  delay(DELAY_A_MS);
  }
  analogWrite(EXTLED7, 0);

  ///digitalWrite(EXTLED8, HIGH);   // turn the LED on (HIGH is the voltage level)
  ///delay(1000);                       // wait for a second
  ///digitalWrite(EXTLED8, LOW);    // turn the LED off by making the voltage LOW
  for(int i = 0; i < 255; i++)
  {
	  analogWrite(EXTLED8, i);
	  delay(DELAY_A_MS);
  }
  analogWrite(EXTLED8, 0);

  //digitalWrite(INTLEDR, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);                       // wait for a second
  //digitalWrite(INTLEDR, LOW);    // turn the LED off by making the voltage LOW
  for(int i = 0; i < 255; i++)
  {
	  analogWrite(INTLEDR, i);
	  delay(DELAY_A_MS);
  }
  analogWrite(INTLEDR, 0);

  ///digitalWrite(INTLEDG, HIGH);   // turn the LED on (HIGH is the voltage level)
  ///delay(1000);                       // wait for a second
  ///digitalWrite(INTLEDG, LOW);    // turn the LED off by making the voltage LOW
  for(int i = 0; i < 255; i++)
  {
	  analogWrite(INTLEDG, i);
	  delay(DELAY_A_MS);
  }
  analogWrite(INTLEDG, 0);

  ///digitalWrite(INTLEDB, HIGH);   // turn the LED on (HIGH is the voltage level)
  ///delay(1000);                       // wait for a second
  ///digitalWrite(INTLEDB, LOW);    // turn the LED off by making the voltage LOW
  for(int i = 0; i < 255; i++)
  {
	  analogWrite(INTLEDB, i);
	  delay(DELAY_A_MS);
  }
  analogWrite(INTLEDB, 0);

}