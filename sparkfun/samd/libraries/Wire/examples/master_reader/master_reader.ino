// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006
// Updated 22 October 2020

// This example code is in the public domain.


#include <Wire.h>

#define SEN_ADDR    0x69
#define REG_REQUEST 0x14

void setup()
{
  Wire.begin();      
  Serial.begin(115200);  // Start serial for output
}

void loop()
{
  Wire.beginTransmission(SEN_ADDR); // Begin at sensor's address
  Wire.write(REG_REQUEST); //Request information from specified register
  Wire.endTransmission(); 

  Wire.requestFrom(SEN_ADDR, 2); // Expecting two bytes
  while(Wire.available())    // Sensor may send less than requested
  { 
    uint8_t c = Wire.read(); // Read single byte
    Serial.println(c, HEX); // Print byte as a hex value
  }

  delay(500);
}
