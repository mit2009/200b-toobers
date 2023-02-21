/***************************************************

 2.00b LEDandButtonTest!

 A simple little LED and Button Test

 Created for the 2023 MIT 2.00b Toy Product Design Class
 Questions?: hit us up on #ask-the-tas on Slack
 Cheers, [Victor Hung](vhung@mit.edu)
 MIT License


 ****************************************************/

#include <FastLED.h>

#define NUM_LEDS 4 // How many LEDs do we have?
#define LED_PIN 4  // What pin is our LEDs connected to?

CRGB leds[NUM_LEDS]; // Initialize the values of LEDs

/**
 * setup
 * --
 * The setup() function is called when a sketch starts. Use it to initialize variables, pin modes, start using libraries, etc.
 * This function will only run once, after each powerup or reset of the Arduino board.
 */
void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS); // Tell FastLED about what type of LEDs we have, how many we have, and where they are
  FastLED.setBrightness(255);                            // Tell FastLED we will be providing brightness values from 0 - 255 inclusive
  pinMode(8, INPUT_PULLUP);                              // initialize pin 8 as an input (the Red Button)
                                                         // Note that 255 is equivalent to 2^8 - 1, or the amount of information you can store in a byte
}

/**
 * loop
 * --
 * The loop() function runs over and over again forever. We are using it to control the color our LED
 */
void loop()
{
  if (digitalRead(8) == LOW) // When pin 8 is low, do the following
  {
    setLed(0, 255, 0, 0);   // Set the first LED to red
    delay(500);             // Wait half a second
    setLed(0, 0, 255, 0);   // Set the first LED to green
    delay(500);             // Wait half a second
    setLed(0, 255, 0, 255); // Set the first LED to purple
    delay(500);             // Wait half a second
    clearLed(0);            // Clear out the values written to the first LED
  }
}
/**
 * setLed
 * @param ledId the address of the LED you want to set
 * @param r     the amount of red the LED should show
 * @param g     the amount of green the LED should show
 * @param b     the amount of blue the LED should show
 * --
 * The setLed() function sets the color value for the specified LED and asks FastLED to update the LEDs
 */
void setLed(int ledId, int r, int g, int b)
{
  leds[ledId] = CRGB(r, g, b);
  FastLED.show();
}

/**
 * clearLed
 * @param ledId the address of the LED you want to set
 * --
 * The clearLed() function clears the color value for the specified LED and asks FastLED to update the LEDs
 */
void clearLed(int ledId)
{
  leds[ledId] = CRGB(0, 0, 0);
  FastLED.show();
}
