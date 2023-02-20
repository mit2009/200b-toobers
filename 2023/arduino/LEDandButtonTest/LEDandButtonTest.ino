/***************************************************

 2.00b LEDandButtonTest! 
 
 A simple little LED and Button Test
 
 Created for the 2023 MIT 2.00b Toy Product Design Class
 Questions?: hit us up on #ask-the-tas on Slack
 Cheers, [Victor Hung](vhung@mit.edu)
 MIT License
 
 
 ****************************************************/

#include <FastLED.h>

#define NUM_LEDS 4
#define LED_PIN 4

CRGB leds[NUM_LEDS];

// the setup function runs once when you press reset or power the board
void setup() {

	FastLED.addLeds<WS2812,LED_PIN,RGB>(leds,NUM_LEDS);
	FastLED.setBrightness(255);

  // initialize pin 8 as an input (the Red Button).
  pinMode(8, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(8) == LOW) {            // This is an if statement blah blah
    setLed(0, 255, 0, 0);                 // This sets the blah blah           
    delay(500);   
    setLed(0, 0, 255, 0);
    delay(500);   
    setLed(0, 255, 0, 255);
    delay(500);
    clearLed(0);
  }
}

void setLed(int ledId, int r, int g, int b) {
  leds[ledId] = CRGB(r, g, b);
  FastLED.show();
}

void clearLed(int ledId) {
  leds[ledId] = CRGB(0, 0, 0);
  FastLED.show();
}
