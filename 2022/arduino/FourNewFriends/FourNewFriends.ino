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
  // initialize pin 3 as an output (the Green LED).
  pinMode(3, OUTPUT);
  // initialize pin 4 as an output (the Blue LED).
  pinMode(4, OUTPUT);
  // initialize pin 5 as an output (the Yellow LED).
  pinMode(5, OUTPUT);
  // initialize pin 6 as an input (the Red Button).
  pinMode(6, INPUT_PULLUP);
  // initialize pin 7 as an input (the Green Button).
  pinMode(7, INPUT_PULLUP);
  // initialize pin 8 as an input (the Blue Button).
  pinMode(8, INPUT_PULLUP);
  // initialize pin 9 as an input (the Yellow Button).
  pinMode(9, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(6) == LOW) {         // If we detect that input 6 (Red Button) is LOW (0v)
    digitalWrite(2, HIGH);             // Write HIGH (5v) to pin 2 (the Red LED!)
    digitalWrite(3, LOW);              // Write LOW (0v) to all the other pins
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  
  if (digitalRead(7) == LOW) {         // If we detect that input 7 (Green Button) is LOW (0v)
    digitalWrite(3, HIGH);             // Write HIGH (5v) to pin 3 (the Green LED!)
    digitalWrite(2, LOW);              // Write LOW (0v) to all the other pins
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  
  if (digitalRead(8) == LOW) {         // If we detect that input 8 (Blue Button) is LOW (0v)
    digitalWrite(4, HIGH);             // Write HIGH (5v) to pin 4 (the Blue ED!)
    digitalWrite(2, LOW);              // Write LOW (0v) to all the other pins
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
  }
  
  if (digitalRead(9) == LOW) {         // If we detect that input 9 (Yellow Button) is LOW (0v)
    digitalWrite(5, HIGH);             // Write HIGH (5v) to pin 5 (the YellowLED!)
    digitalWrite(2, LOW);              // Write LOW (0v) to all the other pins
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }

  delay(10);
}
