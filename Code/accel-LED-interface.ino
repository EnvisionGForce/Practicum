/* What I have so far. 
Determines cartesian direction (in radians) and magnitude 
of input vector from ADXL345 in the form: x, y (ex: 25,-53).
Need to add categorization for magnitude and direction,
to select particular LED and color. */

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

}

void loop() {
  // put your main code here, to run repeatedly:

}
