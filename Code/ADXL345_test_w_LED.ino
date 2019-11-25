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

  adxl.setRangeSetting(4);           // Give the range settings
                                      // Accepted values are 2g, 4g, 8g or 16g
                                      // Higher Values = Wider Measurement Range
                                      // Lower Values = Greater Sensitivity

  adxl.setRate(6.25);                 // Set data output rate (Hz)

  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                      // Default: Set to 0
                                      // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library 

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in variables declared above x,y,z

}

void loop() {
 
  int foo_x = x, foo_y = y; 

//-----------------------------Computation and assignment-------------------------------
  if (x>0) {              // If x-component is within cartesian quadrant 1 or 4
    angle = atan2(x, y);    // (In radians)
  }
  else {                  // If x-component is within cartesian quadrant 2 or 3
    angle = atan2(x, y) + PI; // (In radians)
  }

  mag = sqrt(sq((long) x)+sq((long) y));  // Determines magnitude (independent of cartesian quadrant)

  // Print values x, y, angle, and mag
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("; y: ");
  Serial.println(y);
  Serial.print("Angle:");  
  Serial.println(angle, 4); // Display direction (in radians)
  Serial.print("Mag:"); 
  Serial.println(mag);   // Display magnitude

  if (mag<30) {  // 
    strip.setPixelColor(6, 0, 0, 0);       // Turn off 6th pixel 
    strip.show();
    strip.setPixelColor(6, 0, 255, 0);     //  Set 6th pixel to Green
    strip.show();
    Serial.println("Color: Green");
    Serial.print('\n');
  }
  else if (mag<40) {   // 
    strip.setPixelColor(6, 0, 0, 0);       // Turn off 6th pixel 
    strip.show();    
    strip.setPixelColor(6, 124, 252, 0);     //  Set 6th pixel to Green-yellow
    strip.show();
    Serial.println("Color: Green-yellow");
    Serial.print('\n');
  }
  else if (mag<60) {   // 
    strip.setPixelColor(6, 0, 0, 0);       // Turn off 6th pixel 
    strip.show();    
    strip.setPixelColor(6, 255, 255, 0);     //  Set 6th pixel to Yellow
    strip.show();
    Serial.println("Color: Yellow");
    Serial.print('\n');
  }
  else if (mag<80) {   // 
    strip.setPixelColor(6, 0, 0, 0);       // Turn off 6th pixel 
    strip.show();    
    strip.setPixelColor(6, 225, 100, 0);     //  Set 6th pixel to Yellow-Orange
    strip.show();
    Serial.println("Color: Yellow-Orange");
    Serial.print('\n');
  }
  else if (mag<100) {   // 
    strip.setPixelColor(6, 0, 0, 0);       // Turn off 6th pixel 
    strip.show();    
    strip.setPixelColor(6, 255, 50, 0);     //  Set 6th pixel to Orange
    strip.show();
    Serial.println("Color: Orange");
    Serial.print('\n');
  }
  else if (mag<120) {   // 
    strip.setPixelColor(6, 0, 0, 0);       // Turn off 6th pixel 
    strip.show();    
    strip.setPixelColor(6, 255, 0, 0);     //  Set 6th pixel to Red
    strip.show();
    Serial.println("Color: Red");
    Serial.print('\n');
  }
//-------------------------------------------------------------------------------------- 

  while (foo_x == x && foo_y == y) {
    adxl.readAccel(&x, &y, &z);   // Poll the accelerometer
  }

}
