/*  This program continuously polls output data
 *  from the ADXL. Once new (i.e. different from the
 *  previous output) x, y values arrive from the ADXL, 
 *  the program exits the polling loop, computes the 
 *  new magnitude and direction (in rads), and prints 
 *  the values x, y, mag, and angle.
 */

#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library
#include <math.h>                     // Arduino math library

int x,y,z;        // Global variables
float angle, mag;

ADXL345 adxl = ADXL345(10);           // SET TO SPI COMMUNICATION MODE, ADXL345(CS_PIN);

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

  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in variables declared above x,y,z

}

void loop() {
 
  int foo_x = x, foo_y = y; 

//---------------------------Computations and LED assignment----------------------------
  if (x>0) {              // If x-component is within cartesian quadrant 1 or 4
    angle = atan2(x, y);    // (In radians)
  }
  else {                  // If x-component is within cartesian quadrant 2 or 3
    angle = atan2(x, y) + PI; // (In radians)
  }

  mag = sqrt(sq(x)+sq(y));  // Determines magnitude (independent of cartesian quadrant)
//-------------------------------------------------------------------------------------- 

  // Print values x, y, angle, and mag
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("; y: ");
  Serial.println(y);
  Serial.print("Angle:");  
  Serial.println(angle, 4); // Display direction (in radians)
  Serial.print("Mag:"); 
  Serial.println(mag, 4);   // Display magnitude

  while (foo_x == x && foo_y == y) {
    adxl.readAccel(&x, &y, &z);   // Poll accelerometer output data
  }
  
  //delay(160); //160 = 1 sample per 1 print. 80 = 1 sample per 2 prints. etc...

}
