void setup() {
  Serial.begin(9600);
}


void loop() {
	char inputBuffer[40];
	int inputBufferPtr = 0;
  if(Serial.available())
  {
	  while(Serial.available())
	  {
		  inputBuffer[inputBufferPtr] = Serial.read();
		  inputBufferPtr++;
	  }
	  inputBuffer[inputBufferPtr] = 0;
	  delay(3000);
    Serial.write(inputBuffer);   // read it and send it out Serial1 (pins 0 & 1)
  }

}
