#define BTNPIN 4 

#define SWPIN 9 

void setup() {
	pinMode( BTNPIN, INPUT_PULLUP);
	pinMode( SWPIN, INPUT_PULLUP);
	Serial.begin(9600);
 }

void loop() {
	Serial.print(digitalRead(BTNPIN));
	Serial.print(", ");
	Serial.print(digitalRead(SWPIN));
	Serial.println();
	
	delay(200);
}