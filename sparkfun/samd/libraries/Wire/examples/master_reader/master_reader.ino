// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Wire.beginTransmission(0x28);
  Wire.write(0xFD);
  Wire.requestFrom(0x28, 1);    // request 6 bytes from slave device #2
  Wire.endTransmission();

  while(Wire.available())    // slave may send less than requested
  { 
    uint8_t c = Wire.read(); // receive a byte as character
    Serial.println(c, HEX);         // print the character
  }

  delay(500);
}
