#include <Adafruit_NeoPixel.h>

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
  // put your setup code here, to run once:
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // put your main code here, to run repeatedly:

  //strip.setPixelColor(n, red, green, blue);
  // 0, 255, 0 - Green
  // 255, 150, 0 - Yellow
  // 255, 50, 0 - Orange
  // 255, 0, 0 - Red

  colorTran(1000);
  
  //strip.setPixelColor(0, 255, 150, 0);         //  Set pixel's color (in RAM)
  //strip.show();                          //  "Push" the color data to the strip
  //colorWipe(strip.Color(255,   0,   0), 50); // Red
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void colorTran(int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, 0, 255, 0);     //  Set pixel's color to Green
    strip.show();                          //  Update strip to match (comment-out to turn off)
    delay(wait);                           //  Pause for a moment

    strip.setPixelColor(i, 255, 150, 0);     //  Set pixel's color to Yellow
    strip.show();                          //  Update strip to match (comment-out to turn off)
    delay(wait);                           //  Pause for a moment

    strip.setPixelColor(i, 255, 50, 0);     //  Set pixel's color to Orange
    strip.show();                          //  Update strip to match (comment-out to turn off)
    delay(wait);                           //  Pause for a moment

    strip.setPixelColor(i, 255, 0, 0);     //  Set pixel's color to Red
    strip.show();                          //  Update strip to match (comment-out to turn off)
    delay(wait);                           //  Pause for a moment

    strip.setPixelColor(i, 0, 0, 0);       //  Turn off pixel
    strip.show();                          //  Update strip to match
  }
}

    
