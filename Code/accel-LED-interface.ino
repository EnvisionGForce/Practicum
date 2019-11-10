void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
float x = 3;
float y = -4;
float angle;
float mag;

if (x>0) {
  angle = atan(x/y);
}
else {
  angle = atan(x/y) + PI;
}

mag = sqrt(sq(x)+sq(y));

Serial.println(angle, 8);
Serial.println(mag, 4);

}

void loop() {
  // put your main code here, to run repeatedly:

}
