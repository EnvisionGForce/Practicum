/*  This program continuously polls output data
 *  from the ADXL, and lights 1 of 12 LEDs based on the data. 
 *  Once new (and different) x, y values arrive from 
 *  the ADXL, the program exits the polling loop, 
 *  computes the new magnitude and direction (in rads), 
 *  and lights the appropriate LED. LED activation
 *  thresholds can be set within the polling loop.
 */

#include <SparkFun_ADXL345.h>       // SparkFun ADXL345 Library
#include <math.h>                   // Arduino math library
#include <Adafruit_NeoPixel.h>      // Adafruit NeoPixel library

// Global variables
int x,y,z;
int LED_on, LED_off;
int mag;
float angle;

ADXL345 adxl = ADXL345(10);         // SET TO SPI COMMUNICATION MODE, ADXL345(CS_PIN);

#define LED_PIN    6
#define LED_COUNT 12

// Declare NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)

void setup() {

  //Serial.begin(9600);               // Start the serial terminal, set baud rate
  
  adxl.powerOn();                   // Power on the ADXL345

  adxl.setRangeSetting(2);          // Give the range settings
                                    // Accepted values are 2g, 4g, 8g or 16g
                                    // Higher Values = Wider Measurement Range
                                    // Lower Values = Greater Sensitivity

  adxl.setRate(100);                // Set ADXL data output rate (Hz)

  adxl.setSpiBit(0);                // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                    // Default: Set to 0
                                    // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library 

  strip.begin();                    // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                     // Turn OFF all pixels ASAP
  strip.setBrightness(50);          // Set BRIGHTNESS to about 1/5 (max = 255)

  adxl.readAccel(&x, &y, &z);       // Read the accelerometer values and store them in variables declared above x,y,z

}

void loop() {
 
  int foo_x = x, foo_y = y; // Store old x, y values

//-----------------------------Angle, Mag Computation-------------------------------

  angle = atan2((double) y, (double) x);    // Determines direction (rads): 0-> 180 and 0-> -180
  mag = sqrt(sq((long) x)+sq((long) y));  // Determines magnitude

  // Print values x, y, angle, and mag (for testing purposes)
  Serial.print("x: ");
  Serial.print(x);          // Display x value
  Serial.print("; y: ");
  Serial.println(y);        // Display y value
  Serial.print("Angle:");  
  Serial.println(angle, 4); // Display direction (in radians)
  Serial.print("Mag:"); 
  Serial.println(mag);      // Display magnitude

//-----------------------------Choose which LED to light-------------------------------
  if (angle <= -1.57) {        // If angle is between -90 - -180
    if (angle <= -2.62) {      // -181 - -150
      LED_on = 6;
    }
    else if (angle <= -2.09) { // -149 - -120
      LED_on = 5;
    }
    else  {                    // -121 - -90
      LED_on = 4;
    }
  }  

  else if (angle < 0)  {       // If angle is between 0 - -90
    if (angle <= -1.05) {      // -89 - -60
      LED_on = 3;
    }
    else if (angle <= -0.52) { // -59 - -30
      LED_on = 2;
    }
    else  {                    // -29 - 0
      LED_on = 1;
    }
  }

  else if (angle <= 1.57) {    // If angle is between 0-90
    if ( angle <= 0.52) {      // 0-30
      LED_on = 0;
    }
    else if (angle <= 1.05) {  // 31-60
      LED_on = 11;
    }
    else  {                    // 61-90
      LED_on = 10;
    }
  }

  else if (angle <= 3.142) {  // If angle is between 91-180
    if (angle <= 2.09) {      // 91-120
      LED_on = 9;
    }
    else if (angle <= 2.62) { // 121-150
      LED_on = 8;
    }
    else  {                   // 151-180
      LED_on = 7;
    }
  }

//-----------------------------Choose color to light-------------------------------
  if (mag<100) {  // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old LED 
    strip.show();
    strip.setPixelColor(LED_on, 0, 255, 0);      //  Set new LED to Green
    strip.show();
  }
  else if (mag<130) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old LED 
    strip.show();    
    strip.setPixelColor(LED_on, 124, 252, 0);    //  Set new LED to Green-yellow
    strip.show();
  }
  else if (mag<160) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old LED 
    strip.show();    
    strip.setPixelColor(LED_on, 255, 255, 0);    //  Set new LED to Yellow
    strip.show();
  }
  else if (mag<190) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old LED 
    strip.show();    
    strip.setPixelColor(LED_on, 225, 100, 0);    //  Set new LED to Yellow-Orange
    strip.show();
  }
  else if (mag<220) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old LED 
    strip.show();    
    strip.setPixelColor(LED_on, 255, 50, 0);     //  Set new LED to Orange
    strip.show();
  }
  else {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old LED 
    strip.show();    
    strip.setPixelColor(LED_on, 255, 0, 0);      //  Set new LED to Red
    strip.show();
  }
  
  LED_off = LED_on; //Store old LED value
  
  while (foo_x == x && foo_y == y) {  // Polling loop (sits here waiting for new and different values) 
    adxl.readAccel(&x, &y, &z);   
    
    while (abs(x)<10 && abs(y)<10) {  // Set LED activation threshold
    adxl.readAccel(&x, &y, &z);   
    strip.setPixelColor(LED_off, 0, 0, 0);
    strip.show();
    }
  }

}
