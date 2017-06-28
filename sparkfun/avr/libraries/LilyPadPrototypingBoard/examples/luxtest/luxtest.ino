#define INTLED0 15
#define INTLED1 16
#define INTLED2 17
#define INTLED3 18
#define INTLED4 19
#define INTLED5 20

#define LUXPIN A2

void setup() {
  Serial.begin(9600);
  pinMode(LUXPIN, INPUT);

  pinMode(INTLED0, INPUT); //use OUTPUT for strong drive (Bright!)
  pinMode(INTLED1, INPUT); //use OUTPUT for strong drive (Bright!)
  pinMode(INTLED2, INPUT); //use OUTPUT for strong drive (Bright!)
  pinMode(INTLED3, INPUT); //use OUTPUT for strong drive (Bright!)
  pinMode(INTLED4, INPUT); //use OUTPUT for strong drive (Bright!)
  pinMode(INTLED5, INPUT); //use OUTPUT for strong drive (Bright!)
}


void loop()
{
	int luxReading = analogRead(LUXPIN);
    Serial.println(luxReading);   // read it and send it out Serial1 (pins 0 & 1)
	drawBarGraph(luxReading);

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