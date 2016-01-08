/**************************************************************************
 *                                                                         *
 * Qduino Mini library w/MAX1704* Driver & RGB PWM control                 *
 *                                                                         *
 * MAX1704+ Driver Forked From:                                            *
 * Matthew Newberry                                                        *
 * mattnewberry@me.com                                                     *
 *                                                                         *
 ***************************************************************************
 *                                                                         * 
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU License.                                  *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU License V2 for more details.                                        *
 *                                                                         *
 ***************************************************************************/

#include "Arduino.h"
#include "Qduino.h"
#include "Wire.h"

void qduino::setup(){
    
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    pinMode(11, OUTPUT);
    digitalWrite(11, HIGH);
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
}

void qduino::setRGB(int r, int g, int b){
    
    // ratio for R:G:B is 4:7:7 for forward voltage
    
    r = 255 - r; // set all values to opposite values
    g = 255 - g; // because LED is common anode
    b = 255 - b;
    
    int newr = map(r, 0, 255, 0, 146);
    
    analogWrite(10, newr);
    analogWrite(11, g);
    analogWrite(13, b);
}

void qduino::setRGB(String color){
    
    int intcolor;
    
    if(color == "red") { intcolor = 1; }
    if(color == "green") { intcolor = 2; }
    if(color == "blue") { intcolor = 3; }
    if(color == "cyan") { intcolor = 4; }
    if(color == "pink") { intcolor = 5; }
    if(color == "white") { intcolor = 6; }
    if(color == "purple") { intcolor = 7; }
    if(color == "yellow") { intcolor = 8; }
    if(color == "orange") { intcolor = 9; }
    
    switch (intcolor) {
        case 1:
            analogWrite(10, 0);
            analogWrite(11, 255);
            analogWrite(13, 255);
            break;
        case 2:
            analogWrite(10, 255);
            analogWrite(11, 0);
            analogWrite(13, 255);
            break;
        case 3:
            analogWrite(10, 255);
            analogWrite(11, 255);
            analogWrite(13, 0);
            break;
        case 4:
            analogWrite(10, 255);
            analogWrite(11, 0);
            analogWrite(13, 0);
            break;
        case 5:
            analogWrite(10, 109);
            analogWrite(11, 255);
            analogWrite(13, 0);
            break;
        case 6:
            analogWrite(10, 109);
            analogWrite(11, 0);
            analogWrite(13, 0);
            break;
        case 7:
            analogWrite(10, 210);
            analogWrite(11, 255);
            analogWrite(13, 0);
            break;
        case 8:
            analogWrite(10, 100);
            analogWrite(11, 0);
            analogWrite(13, 255);
            break;
        case 9:
            analogWrite(10, 109);
            analogWrite(11, 150);
            analogWrite(13, 255);
            break;
    }
}

void qduino::rainbow(int duration){
    
unsigned int rgbColor[3];
 
    int newduration = map(duration, 1, 5, 500, 3000);
    
  // Start off with red.
  rgbColor[0] = 255;
  rgbColor[1] = 0;
  rgbColor[2] = 0;  
 
  // Choose the colours to increment and decrement.
  for (int decColor = 0; decColor < 3; decColor += 1) {
    int incColor = decColor == 2 ? 0 : decColor + 1;
 
    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColor[decColor] -= 1;
      rgbColor[incColor] += 1;
      
      analogWrite(10, rgbColor[0]);
      analogWrite(11, rgbColor[1]);
      analogWrite(13, rgbColor[2]);
      delayMicroseconds(newduration);
    }
  }
}

void qduino::ledOff(){
    
    analogWrite(10, 255);
    analogWrite(11, 255);
    analogWrite(13, 255);
    
}

int fuelGauge::chargePercentage(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_SOC,msb,lsb);

  int fraction = lsb / 256;
  int percentage = msb + fraction;

  return percentage;
}

void fuelGauge::setup(){
    reset();
    performCommand(MAX1704_QUICK_START, 0x00); // aka quickStart();
}

void fuelGauge::reset(){

  performCommand(MAX1704_POWER_ON_RESET, 0x00);
}

char fuelGauge::getVersion(){

  int value = 0;
  byte msb = 0;
  byte lsb = 0;
  readFrom(MAX1704_VERSION, msb, lsb);
  
    value  = 0xFF00 & (msb<<8);
    value |=   0xFF & lsb;

  return value;
}

void fuelGauge::setThreshold(uint8_t level){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_CONFIG);
  Wire.write(MAX1704_ALERT_LEVEL);
  Wire.write(32 - level);
  Wire.endTransmission();
}

int fuelGauge::currentThreshold(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_CONFIG,msb,lsb);
  byte threshold = lsb & 0x1f;

  return 32 - threshold;
}

boolean fuelGauge::inAlert(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_CONFIG,msb,lsb);
  byte alert = (lsb >>5) & 0x01;

  return int(alert) == 1;
}

boolean fuelGauge::inSleep(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_CONFIG,msb,lsb);
  byte sleep = (lsb >>7) & 0x01; 

  return int(sleep) == 1;
}

void fuelGauge::goToSleep(){
  byte msb = 0;
  byte lsb = 0;

  // Get the current config so we don't wipe any previous settings
  readFrom(MAX1704_CONFIG,msb,lsb);

  // Set SLEEP config bit to 1 to enable
  lsb |= (1<<7);

  // Update config
  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_CONFIG);
  Wire.write(msb);
  Wire.write(lsb);
  Wire.endTransmission();

  // This delay is here to ensure it's fully asleep before moving on
  delay(150);
}

void fuelGauge::wakeUp(){
  byte msb = 0;
  byte lsb = 0;

  // Get the current config so we don't wipe any previous settings
  readFrom(MAX1704_CONFIG,msb,lsb);
  // Set SLEEP config bit to 0 to disable
  lsb &= ~(1<<7);

  // Update config
  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_CONFIG);
  Wire.write(msb);
  Wire.write(lsb);
  Wire.endTransmission();

  // This delay is here to ensure it's fully awake before moving on
  delay(150); 
}

void fuelGauge::performCommand(byte address, int value){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_COMMAND);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

void fuelGauge::readFrom(byte address, byte &msb, byte &lsb){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(MAX1704_ADDR, 2);

  int numread = Wire.available();
  //if (numread == 2) {
  msb = Wire.read();
  lsb = Wire.read();
  //}
  Wire.endTransmission();
}

