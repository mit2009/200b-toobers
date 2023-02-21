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
#define BUTTON_1 8 // What pin is the first button connected to?
#define BUTTON_2 7 // What pin is the second button connected to?
#define BUTTON_3 6 // What pin is the third button connected to?
#define BUTTON_4 5 // What pin is the fourth button connected to?

CRGB leds[NUM_LEDS]; // Initialize the values of LEDs

/**
 * setup
 * --
 * The setup() function is called when a sketch starts. Use it to initialize variables, pin modes, start using libraries, etc.
 * This function will only run once, after each powerup or reset of the Arduino board.
 */
void setup() {

  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS); // Tell FastLED about what type of LEDs we have, how many we have, and where they are
  FastLED.setBrightness(255);                            // Tell FastLED we will be providing brightness values from 0 - 255 inclusive
                                                         // Note that 255 is equivalent to 2^8 - 1, or the amount of information you can store in a byte

  pinMode(BUTTON_1, INPUT_PULLUP); // initialize our button pins as inputs
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
}

/**
 * loop
 * --
 * The loop() function runs over and over again forever. We are using it to control the color our LED
 */
void loop() {
  if (digitalRead(BUTTON_1) == LOW) // When the first button is pressed, do the following
  {
    setLed(0, 255, 0, 0);  // Set the first LED to red
                           // Note that we start counting at 0 instead of 1 in code
    delay(100);            // Wait a tenth of a second
    clearLed(0);           // Clear the value written to the first LED
    delay(100);            // Wait a tenth of a second
    setLed(0, 255, 50, 0); // Set the first LED to orange-ish
    delay(100);            // Wait a tenth of a second
    clearLed(0);           // Clear the value written to the first LED
  }

  if (digitalRead(BUTTON_2) == LOW) // When the second button is pressed, do the following
  {                                 // Blink the second LED green and then lime green (see above for more details)
    setLed(1, 0, 255, 0);
    delay(100);
    clearLed(1);
    delay(100);
    setLed(1, 0, 255, 50);
    delay(100);
    clearLed(1);
  }

  if (digitalRead(BUTTON_3) == LOW) // When the third button is pressed, do the following
  {                                 // Blink the third LED blue and then lighter blue
    setLed(2, 0, 0, 255);
    delay(100);
    clearLed(2);
    delay(100);
    setLed(2, 50, 0, 255);
    delay(100);
    clearLed(2);
  }

  if (digitalRead(BUTTON_4) == LOW) // When the forth button is pressed, do the following
  {                                 // Blink the forth LED yellow and then yellow greenish
    setLed(3, 200, 255, 0);
    delay(100);
    clearLed(3);
    delay(100);
    setLed(3, 200, 255, 50);
    delay(100);
    clearLed(3);
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
void setLed(int ledId, int r, int g, int b) {
  leds[ledId] = CRGB(r, g, b);
  FastLED.show();
}

/**
 * clearLed
 * @param ledId the address of the LED you want to set
 * --
 * The clearLed() function clears the color value for the specified LED and asks FastLED to update the LEDs
 */
void clearLed(int ledId) {
  leds[ledId] = CRGB(0, 0, 0);
  FastLED.show();
}
