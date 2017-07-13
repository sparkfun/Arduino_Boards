/*
LilyPad Prototyping Board
Demo (Factory-Installed) Code
SparkFun Electronics
https://www.sparkfun.com/products/14346

This code is covered by the MTT license and is completely free for any use.

******************************************************************************/

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

#define BTNPIN 4 

#define SWPIN 9 

#define LUXPIN A2

#define DELAY_A_MS 2

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LUXPIN, INPUT);
	pinMode( BTNPIN, INPUT_PULLUP);
	pinMode( SWPIN, INPUT_PULLUP);
	
  analogWrite(EXTLED6, 0);
  analogWrite(EXTLED7, 0);
  analogWrite(EXTLED8, 0);
  analogWrite(INTLEDR, 0);
  analogWrite(INTLEDG, 0);
  analogWrite(INTLEDB, 0);

}

int modeSelected = 0;

void loop()
{
int luxReading;
byte temp_TCCR3A;
byte temp_TCCR3B;

	switch(modeSelected)
	{
		case 0:
			digitalWrite( INTLED0, 0 );
			digitalWrite( INTLED1, 0 );
			digitalWrite( INTLED2, 0 );
			digitalWrite( INTLED3, 0 );
			digitalWrite( INTLED4, 0 );
			digitalWrite( INTLED5, 0 );

			pinMode(INTLED0, OUTPUT);
			pinMode(INTLED1, OUTPUT);
			pinMode(INTLED2, OUTPUT);
			pinMode(INTLED3, OUTPUT);
			pinMode(INTLED4, OUTPUT);
			pinMode(INTLED5, OUTPUT);

			pinMode(EXTLED5, OUTPUT);
			pinMode(EXTLED6, OUTPUT);
			pinMode(EXTLED7, OUTPUT);
			pinMode(EXTLED8, OUTPUT);
			pinMode(INTLEDR, OUTPUT);
			pinMode(INTLEDG, OUTPUT);
			pinMode(INTLEDB, OUTPUT);

			
			digitalWrite(INTLED0, HIGH);   // turn the LED on (HIGH is the voltage level)
			delay(500);                       // wait for a second
			digitalWrite(INTLED0, LOW);    // turn the LED off by making the voltage LOW
			
			digitalWrite(INTLED1, HIGH);   // turn the LED on (HIGH is the voltage level)
			delay(500);                       // wait for a second
			digitalWrite(INTLED1, LOW);    // turn the LED off by making the voltage LOW
			
			digitalWrite(INTLED2, HIGH);   // turn the LED on (HIGH is the voltage level)
			delay(500);                       // wait for a second
			digitalWrite(INTLED2, LOW);    // turn the LED off by making the voltage LOW
			
			digitalWrite(INTLED3, HIGH);   // turn the LED on (HIGH is the voltage level)
			delay(500);                       // wait for a second
			digitalWrite(INTLED3, LOW);    // turn the LED off by making the voltage LOW
			
			digitalWrite(INTLED4, HIGH);   // turn the LED on (HIGH is the voltage level)
			delay(500);                       // wait for a second
			digitalWrite(INTLED4, LOW);    // turn the LED off by making the voltage LOW
			
			digitalWrite(INTLED5, HIGH);   // turn the LED on (HIGH is the voltage level)
			delay(500);                       // wait for a second
			digitalWrite(INTLED5, LOW);    // turn the LED off by making the voltage LOW
			
			digitalWrite(EXTLED5, HIGH);   // turn the LED on (HIGH is the voltage level)
			delay(500);                       // wait for a second
			digitalWrite(EXTLED5, LOW);    // turn the LED off by making the voltage LOW

			for(int i = 0; i < 255; i++)
			{
				analogWrite(EXTLED6, i);
				delay(DELAY_A_MS);
			}
			analogWrite(EXTLED6, 0);
			
			for(int i = 0; i < 255; i++)
			{
				analogWrite(EXTLED7, i);
				delay(DELAY_A_MS);
			}
			analogWrite(EXTLED7, 0);
			
			for(int i = 0; i < 255; i++)
			{
				analogWrite(EXTLED8, i);
				delay(DELAY_A_MS);
			}
			analogWrite(EXTLED8, 0);
			
			for(int i = 0; i < 255; i++)
			{
				analogWrite(INTLEDR, i);
				delay(DELAY_A_MS);
			}
			analogWrite(INTLEDR, 0);
			
			for(int i = 0; i < 255; i++)
			{
				analogWrite(INTLEDG, i);
				delay(DELAY_A_MS);
			}
			analogWrite(INTLEDG, 0);
			
			for(int i = 0; i < 255; i++)
			{
				analogWrite(INTLEDB, i);
				delay(DELAY_A_MS);
			}
			analogWrite(INTLEDB, 0);
		break;
		case 1:
			pinMode(INTLED0, INPUT);
			pinMode(INTLED1, INPUT);
			pinMode(INTLED2, INPUT);
			pinMode(INTLED3, INPUT);
			pinMode(INTLED4, INPUT);
			pinMode(INTLED5, INPUT);
			for(int i = 0; i < 3000; i++)
			{
				luxReading = analogRead(LUXPIN);
				drawBarGraph(luxReading);
				delay(1);
			}
		break;
		case 2:
			digitalWrite( INTLED0, 0 );
			digitalWrite( INTLED1, 0 );
			digitalWrite( INTLED2, 0 );
			digitalWrite( INTLED3, 0 );
			digitalWrite( INTLED4, 0 );
			digitalWrite( INTLED5, 0 );
			//This needs to be undone afterwards
//        // 16 bit timer
//        TCCR3A = 0;
//        TCCR3B = 0;
//        bitWrite(TCCR3B, WGM32, 1);
//        bitWrite(TCCR3B, CS30, 1);
//        timer3_pin_port = portOutputRegister(digitalPinToPort(_pin));
//        timer3_pin_mask = digitalPinToBitMask(_pin);
			//Save TCCR3A and TCCR3B
			temp_TCCR3A = TCCR3A;
			temp_TCCR3B = TCCR3B;
			for (int thisNote = 0; thisNote < 8; thisNote++) {
			
				// to calculate the note duration, take one second
				// divided by the note type.
				//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
				int noteDuration = 1000 / noteDurations[thisNote];
				tone(3, melody[thisNote], noteDuration);
			
				// to distinguish the notes, set a minimum time between them.
				// the note's duration + 30% seems to work well:
				int pauseBetweenNotes = noteDuration * 1.30;
				delay(pauseBetweenNotes);
				// stop the tone playing:
				noTone(3);
			}
			delay(1000);
//			 bitWrite(TIMSK3, OCIE3A, 1);
			TCCR3A = temp_TCCR3A;
			TCCR3B = temp_TCCR3B;
		break;
		case 3:
		break;
		default:
		break;
	}
	if(digitalRead(SWPIN) == 0)
	{
		modeSelected++;
		if(modeSelected > 3) modeSelected = 0;
	}

}

void drawBarGraph( int inputVar )
{
	int increment = (200/7);
	if( inputVar > (increment * 1) )
	{
		digitalWrite(INTLED0, 1);
	}
	else
	{
		digitalWrite(INTLED0, 0);
	}
	if( inputVar > (increment * 2) )
	{
		digitalWrite(INTLED1, 1);
	}
	else
	{
		digitalWrite(INTLED1, 0);
	}
	if( inputVar > (increment * 3) )
	{
		digitalWrite(INTLED2, 1);
	}
	else
	{
		digitalWrite(INTLED2, 0);
	}
	if( inputVar > (increment * 4) )
	{
		digitalWrite(INTLED3, 1);
	}
	else
	{
		digitalWrite(INTLED3, 0);
	}
	if( inputVar > (increment * 5) )
	{
		digitalWrite(INTLED4, 1);
	}
	else
	{
		digitalWrite(INTLED4, 0);
	}
	if( inputVar > (increment * 6) )
	{
		digitalWrite(INTLED5, 1);
	}
	else
	{
		digitalWrite(INTLED5, 0);
	}
	
}
