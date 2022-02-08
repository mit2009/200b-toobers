/***************************************************

 2.00b Toobers! 
 
 The 2022 Let's Play project - a simple simon-esque game.
 Full Source and README can be found here: https://github.com/mit2009/200b-toobers
 Hope you enjoy!
 
 Created for the 2022 MIT 2.00b Toy Product Design Class
 Questions?: hit us up on #ask-the-tas on Slack
 Cheers, [Victor Hung](vhung@mit.edu)
 MIT License
 
 Parts adapted from the DFPlayer sample,
 by [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 ****************************************************/

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11);                  // RX, TX
DFRobotDFPlayerMini myDFPlayer;                           // Create myDFPlayer of the DFPlayer Class
void printDetail(uint8_t type, int value);              

int state = 0;                                            // Create a variable to store the 'state' of the game
                                                          // - State 0: Game is playing starting sequence
                                                          // - State 1: Playing the sequence 
                                                          // - State 2: Waiting user input response
                                                          // - State 3: Game is over! Awaiting user to press green to continue
                                                        
int score = 0;                                            // Keeps track of the score
int sequence[100];                                        // Keeps track of the sequence
int buttonPressed[4] = {false, false, false, false};      // State of each button

int playerSequenceIndex = 0;                              // When the user is playing back the sequence, this keeps track of where in the sequence they are

/*
 * setup
 * 
 * The setup() function is called when a sketch starts. Use it to initialize variables, pin modes, start using libraries, etc. 
 * This function will only run once, after each powerup or reset of the Arduino board.
 */
void setup() {
  mySoftwareSerial.begin(9600);                           // Initiate communication with the DFPlayer
  Serial.begin(115200);                                   // Mostly used for debugging

  for (int i = 2; i < 6; i++) {                           // Set inputs 2, 3, 4, 5 to be OUTPUT pins (LEDs)           
    pinMode(i, OUTPUT);
  }
  
  for (int i = 6; i < 10; i++) {                          // Set inputs 6, 7, 8, 9 to be INPUT pins (Buttons)
    pinMode(i, INPUT_PULLUP);
  }

  generateSequence();
                        
  Serial.println(F("Starting 2.00b Simon!"));             // Print to serial monitor that we're starting!       
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {              // Use softwareSerial to communicate with mp3. If we have trouble,
    Serial.println(F("Unable to begin:"));                // print to the serial monitor so we can see.
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  } else {
    Serial.println(F("DFPlayer Mini online."));          
  }
  
  myDFPlayer.volume(20);                                   // Set volume value. From 0 to 30
  myDFPlayer.play(1);                                      // Play the first mp3! Exciting stuff

  delay(120);                                              // This delay and digital write is timed to turn each light on and off
  for (int i = 2; i < 6; i ++) {                           // to match up with the sound effects
    digitalWrite(i, HIGH);
    delay(400);
    digitalWrite(i, LOW);
  }
  delay(8000);
  state = 1;                                               // We're all set with this state. Let's set the state to 1 to start the sequence playing
}

/*
 * loop
 * 
 * The loop function is called continously - meaning, once it reaches the end, it'll do exactly as 
 * the name suggests. Loop and call the function again! Note that if you have delays() in this function, it means
 * each loop will take longer.
 */
void loop()
{
  if (state == 1) {                                        // This is where we'll play the sequence to the user
    for (int i = 0; i < score + 1; i++) {                  // The number of tones played is one more than the score
      myDFPlayer.play(sequence[i]);                        // Play the tone as defined in our initial 100 tones.
      digitalWrite(sequence[i], HIGH);
      delay(400);
      digitalWrite(sequence[i], LOW);
      delay(100);
    }
    playerSequenceIndex = 0;                               // Reset the player sequence number
    state = 2;                                             // Move to the next sequence
  }

  if (state == 2) {                                        // If we're in this state, we're listening to the user input          
    for (int i = 2; i < 6; i ++) {
      if (digitalRead(i+4) == LOW && buttonPressed[i-2] == false) {
        buttonPressed[i-2] = true;                         // This line is used for debouncing. We can use this technique to prevent
                                                           // a button from being pressed 'multiple times', since the input may be noisy.
                                                           // Once the user presses it, this code will no longer run until they've fully 
                                                           // 'released' the button (see the else if statement below)
                                                           
        myDFPlayer.play(i);                                // Play the message corresponding to 
        digitalWrite(i, HIGH);
        delay(450);
        digitalWrite(i, LOW);
      
        if (sequence[playerSequenceIndex] == i) {
          playerSequenceIndex += 1;
          if (playerSequenceIndex > score) {               // That's all the buttons they need to play!
             score += 1;                                   
             myDFPlayer.play(6);
             delay(800);
             state = 1;                                    // We've updated the state, and now we're returning to the toy playing the sequence
          }                                                // to the player
        } else {
          state = 3;                                       // Player has lost! Update the state to now be in the 'waiting for reset'
          myDFPlayer.play(7); 
          delay(200);
          for (int k = 2; k < 6; k ++) {
            digitalWrite(7-k, HIGH);
            delay(200);
            digitalWrite(7-k, LOW);
          }
          delay(3000);
          myDFPlayer.play(score + 8);
          delay(1000);
          myDFPlayer.play(15);
          delay(3000);
        }
        
      } else if (digitalRead(i+4) == HIGH && buttonPressed[i-2] == true) {
        buttonPressed[i-2] = false;                        // Part of the debouncing system as mentioned above
      }
    }
  }

  if (state == 3) {                                        // Waiting for player to press 
    digitalWrite(3, HIGH);
    if (digitalRead(7) == LOW) {
      playerSequenceIndex = 0;
      score = 0;
      state = 1;
      digitalWrite(3, LOW);
      delay(1000);
    }
  }

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); // Print the detail message from DFPlayer to handle different errors and states.
  }
}

/*
 * generate sequence
 * 
 * helper function that generates a sequence of 100 random tones
 */
void generateSequence() {
  randomSeed(analogRead(0));                              // Nothing is connected to pin A0, which will produce noise. 
                                                          // We can use this noise to generate a random number.
    
  for (int i = 0; i < 100; i++) {                         // Pre-set 100 random tones to be our sequence
    int randomNumber = random(2, 6);
    if (i > 0 && i < 10) {                                // For the first 10 notes of the game, we want each tone to be different.
      while (randomNumber == sequence[i-1]) {             // This prevents the same tone from occuring more than two times in a row
        randomNumber = random(2, 6);
      }
    }
    sequence[i] = randomNumber;
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
