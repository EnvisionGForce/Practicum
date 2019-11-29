/*  This program continuously polls output data
 *  from the ADXL, and lights LED 6 based on the data. 
 *  Once new (i.e. different from the previous output) 
 *  x, y values arrive from the ADXL, the program exits 
 *  the polling loop, computes the new magnitude and 
 *  direction (in rads), and lights LED 6.
 */

#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library
#include <math.h>                     // Arduino math library
#include <Adafruit_NeoPixel.h>        // Adafruit NeoPixel library

int x,y,z;        // Global variables
int LED_on, LED_off;
int mag;
float angle;

ADXL345 adxl = ADXL345(10);           // SET TO SPI COMMUNICATION MODE, ADXL345(CS_PIN);

#define LED_PIN    6
#define LED_COUNT 12

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {

  Serial.begin(9600);                 // Start the serial terminal, set baud rate
  Serial.println("SparkFun ADXL345 Accelerometer Hook Up Guide Example");
  Serial.println();
  
  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(2);           // Give the range settings
                                      // Accepted values are 2g, 4g, 8g or 16g
                                      // Higher Values = Wider Measurement Range
                                      // Lower Values = Greater Sensitivity

  adxl.setRate(6.25);                 // Set data output rate (Hz)

  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                      // Default: Set to 0
                                      // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library 

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)

  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in variables declared above x,y,z

}

void loop() {
 
  int foo_x = x, foo_y = y;
  //LED_off = LED_on;

//-----------------------------Computation-------------------------------
  /*
  if (x>0) {              // If x-component is within cartesian quadrant 1 or 4
    angle = atan2((double) y, (double) x);    // (In radians)
  }
  else {                  // If x-component is within cartesian quadrant 2 or 3
    angle = atan2(y, x) + PI; // (In radians)
  }
  */
  angle = atan2((double) y, (double) x);    // Determines direction (rads): 0-> 180 and 0-> -180
  mag = sqrt(sq((long) x)+sq((long) y));  // Determines magnitude

  // Print values x, y, angle, and mag
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("; y: ");
  Serial.println(y);
  Serial.print("Angle:");  
  Serial.println(angle, 4); // Display direction (in radians)
  Serial.print("Mag:"); 
  Serial.println(mag);   // Display magnitude

//-----------------------------Choose LED-------------------------------
  if (angle <= -1.57) {                    // IF -90 - -180
    if (angle <= -2.62) {      // -181 - -150
      LED_on = 6;
    }
    else if (angle <= -2.09) { // -149 - -120
      LED_on = 7;
    }
    else  {                                    // -121 - -90
      LED_on = 8;
    }
  }  

  else if (angle < 0)  {       // IF 0 - -90
    if (angle <= -1.05) {       // -89 - -60
      LED_on = 9;
    }
    else if (angle <= -0.52) {  // -59 - -30
      LED_on = 10;
    }
    else  {                     // -29 - 0
      LED_on = 11;
    }
  }

  else if (angle <= 1.57) {                         // IF 0-90
    if ( angle <= 0.52) {         // 0-30
      LED_on = 0;
    }
    else if (angle <= 1.05) { // 31-60
      LED_on = 1;
    }
    else  {                                    // 61-90
      LED_on = 2;
    }
  }

  else if (angle <= 3.142) {                    // IF 91-180
    if (angle <= 2.09) {      // 91-120
      LED_on = 3;
    }
    else if (angle <= 2.62) { // 121-150
      LED_on = 4;
    }
    else  {                                    // 151-180
      LED_on = 5;
    }
  }


//-----------------------------Choose Color-------------------------------
  if (mag<0) {  // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old pixel 
    strip.show();
    strip.setPixelColor(LED_on, 0, 255, 0);     //  Set new pixel to Green
    strip.show();
  }
  else if (mag<50) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old pixel 
    strip.show();    
    strip.setPixelColor(LED_on, 124, 252, 0);     //  Set new pixel to Green-yellow
    strip.show();
  }
  else if (mag<70) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old pixel 
    strip.show();    
    strip.setPixelColor(LED_on, 255, 255, 0);     //  Set new pixel to Yellow
    strip.show();
  }
  else if (mag<90) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old pixel 
    strip.show();    
    strip.setPixelColor(LED_on, 225, 100, 0);     //  Set new pixel to Yellow-Orange
    strip.show();
  }
  else if (mag<110) {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old pixel 
    strip.show();    
    strip.setPixelColor(LED_on, 255, 50, 0);     //  Set new pixel to Orange
    strip.show();
  }
  else /*if (mag<130)*/ {   // 
    strip.setPixelColor(LED_off, 0, 0, 0);       // Turn off old pixel 
    strip.show();    
    strip.setPixelColor(LED_on, 255, 0, 0);     //  Set new pixel to Red
    strip.show();
  }
  
  LED_off = LED_on;
  while (foo_x == x && foo_y == y) {
    adxl.readAccel(&x, &y, &z);   // Poll the accelerometer
  }

}
