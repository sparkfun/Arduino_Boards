/*
LilyPad ProtoSnap Plus Activity 10: LilyPixel
SparkFun Electronics
https://www.sparkfun.com/products/14346

Make external LilyPixel boards fade through a rainbow of colors

This sketch was written by SparkFun Electronics,
and is based on NeoPixel Ring simple sketch (c) 2013 Shae Erisson
released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

******************************************************************************/

// Include the NeoPixel library, used to drive addressable LEDs

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// We'll hook up the "DI" sew tab of the LilyPixel
// to pin 10 on the LilyPad Development Board:

#define pixelPin 10

// You can daisy chain many LilyPixel boards together,
// In this demo we're just using one:

#define numPixels 1

// The NeoPixel library needs to know what type of
// addressable LED we're connecting to it.
// This command makes those settings:

Adafruit_NeoPixel lilyPixels = Adafruit_NeoPixel(numPixels, pixelPin, NEO_GRB + NEO_KHZ800);

// Delay value in milliseconds between color changes, make smaller to go faster:

int delayval = 5;

void setup() {

  // Initialize the NeoPixel library:
  
  lilyPixels.begin();
}

void loop() {
  int hue, address;
  unsigned char r,g,b;

  // We'll make all the LilyPixels smoothly change colors through a rainbow.
  // The "hue" is the color value, for the rainbow function we're using
  // it will range from 0 to 767.
  
  for(hue = 0; hue < 767; hue++){

    // Each LilyPixel you've daisy-chained together has an address.
    // The address starts at 0 for the nearest one, 1 for the next, etc.
    // This for loop will step through all the LilyPixels:
    
    for(address=0; address<numPixels; address++){

      // Compute the rainbow r,g,b values from the "hue" (0 to 767)

      rainbow(hue,r,g,b);

      // Set a LilyPixel chosen with address, to a RGB color
      
      lilyPixels.setPixelColor(address,r,g,b);

      // We now must send the color set in the above step to the actual LilyPixel:
  
      lilyPixels.show();
  
      delay(delayval);
    }
  }
}

void rainbow(int hue, unsigned char &r, unsigned char &b, unsigned char &g){

  hue = constrain(hue, 0, 767); // constrain the input value to a range of values from 0 to 767

    // if statement breaks down the "hue" into three ranges:

  if (hue <= 255)       // RANGE 1 (0 - 255) - red to green
  {
    r = 255 - hue;    // red goes from on to off
    g = hue;        // green goes from off to on
    b = 0;             // blue is always off
  }

  else if (hue <= 511)  // RANGE 2 (256 - 511) - green to blue
  {
    r = 0;                     // red is always off
    g = 511 - hue;         // green on to off
    b = hue - 256;          // blue off to on
  }

  else                    // RANGE 3 ( >= 512)- blue to red
  {
    r = hue - 512;         // red off to on
    g = 0;                 // green is always off
    b = 767 - hue;        // blue on to off
  }
}

