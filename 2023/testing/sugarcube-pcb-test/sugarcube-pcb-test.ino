#include <FastLED.h>

#define NUM_LEDS 2
#define DATA_PIN 2

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(57600);
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  pinMode(3, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
}


void loop() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  FastLED.show();


  if (digitalRead(7) == LOW) {
    leds[0] = CRGB(255, 0, 0);
    leds[1] = CRGB(255, 0, 0);
    FastLED.show();
    delay(200);
  }
  if (digitalRead(7) == LOW) {
    leds[0] = CRGB(0, 255, 0);
    leds[1] = CRGB(0, 255, 0);
    FastLED.show();
    delay(200);
  }
  if (digitalRead(7) == LOW) {
    leds[0] = CRGB(0, 0, 255);
    leds[1] = CRGB(0, 0, 255);
    FastLED.show();
    delay(200);
  }
}
