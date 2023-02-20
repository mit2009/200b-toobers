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
#define BUTTON_1 8
#define BUTTON_2 7
#define BUTTON_3 6
#define BUTTON_4 5

CRGB leds[NUM_LEDS];

// the setup function runs once when you press reset or power the board
void setup() {

	FastLED.addLeds<WS2812,LED_PIN,RGB>(leds,NUM_LEDS);
	FastLED.setBrightness(255);

  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(BUTTON_1) == LOW) {            // This is an if statement blah blah
    setLed(0, 255, 0, 0);                 // This sets the blah blah           
    delay(100);
    clearLed(0);
    delay(100);
    setLed(0, 255, 50, 0);                 // This sets the blah blah           
    delay(100);
    clearLed(0);
  }

  if (digitalRead(BUTTON_2) == LOW) {            // This is an if statement blah blah
    setLed(1, 0, 255, 0);                 // This sets the blah blah           
    delay(100);
    clearLed(1);
    delay(100);
    setLed(1, 0, 255, 50);                 // This sets the blah blah           
    delay(100);
    clearLed(1);
  }
  
  if (digitalRead(BUTTON_3) == LOW) {            // This is an if statement blah blah
    setLed(2, 0, 0, 255);                 // This sets the blah blah           
    delay(100);
    clearLed(2);
    delay(100);
    setLed(2, 50, 0, 255);                 // This sets the blah blah           
    delay(100);
    clearLed(2);
  }

  if (digitalRead(BUTTON_4) == LOW) {            // This is an if statement blah blah
    setLed(3, 200, 255, 0);                 // This sets the blah blah           
    delay(100);
    clearLed(3);
    delay(100);
    setLed(3, 200, 255, 50);                 // This sets the blah blah           
    delay(100);
    clearLed(3);
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
