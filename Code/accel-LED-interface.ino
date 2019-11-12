/* What I have so far. 
Determines cartesian direction (in radians) and magnitude 
of input vector from ADXL345 in the form: x, y (ex: 25,-53).
Color selection section determines LED color based on magnitude.
(Need to add categorization for direction, to select individual LED) */

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
float x = 3;    // Example of x-component of input vector
float y = -4;   // Example of y-component of input vector
float angle;    // angle variable
float mag;      // magnitude variable

if (x>0) {              // If vector is within cartesian quadrant 1 or 4
  angle = atan(x/y);    // (In radians)
}
else {                  // If vector is within cartesian quadrant 2 or 3
  angle = atan(x/y) + PI; // (In radians)
}

mag = sqrt(sq(x)+sq(y));  // Determines magnitude (independent of cartesian quadrant)

Serial.println(angle, 8); // Display direction (in radians)
Serial.println(mag, 4);   // Display magnitude
  

/*----- COLOR SELECTION SECTION -----*/
// Determines LED color based on mag

  if (mag<128) {  // 0-.5 G
    strip.setPixelColor(i, 0, 255, 0);     //  Set i-th pixel to Green
    strip.show();                          //  Turn on LED
  }
  else if (mag<256) {   //.5-1 G
    strip.setPixelColor(i, 124, 252, 0);   //  Set i-th pixel to Green-yellow
    strip.show();                          //  Turn on LED
  }
  else if (mag<384) {   //1-1.5 G
    strip.setPixelColor(i, 255, 255, 0);   //  Set i-th pixel to Yellow
    strip.show();                          //  Turn on LED
  }
  else if (mag<512) {   //1.5-2 G
    strip.setPixelColor(i, 225, 100, 0);   //  Set i-th pixel to Yellow-Orange
    strip.show();                          //  Turn on LED
  }
  else if (mag<641) {   //2-2.5 G
    strip.setPixelColor(i, 255, 50, 0);    //  Set i-th pixel to Orange
    strip.show();                          //  Turn on LED
  }
  else (mag<769) {   //2.5-3 G
    strip.setPixelColor(i, 255, 0, 0);     //  Set i-th pixel to Red
    strip.show();                          //  Turn on LED
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
