/***************************************************

 2.00b LEDandButtonTest! 
 
 A simple little LED and Button Test
 
 Created for the 2022 MIT 2.00b Toy Product Design Class
 Questions?: hit us up on #ask-the-tas on Slack
 Cheers, [Victor Hung](vhung@mit.edu)
 MIT License
 
 
 ****************************************************/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pin 2 as an output (the Red LED).
  pinMode(2, OUTPUT);
  // initialize pin 6 as an input (the Red Button).
  pinMode(6, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(6) == LOW) {          
    digitalWrite(2, HIGH);              // Write HIGH (5v) to pin 3 (the LED!)
    delay(100);                         // Delay for 100 milliseconds
    digitalWrite(2, LOW);               // Write LOW (0v) to pin 3
    delay(100);                         // Delay
    digitalWrite(2, HIGH);              // ... and repeat!
    delay(100);
    digitalWrite(2, LOW);
  }
}
