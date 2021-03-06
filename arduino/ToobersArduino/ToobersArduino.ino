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

int MAX_SCORE = 100;
int state = 0;                                            // Create a variable to store the 'state' of the game
                                                          // - State 0: Game is playing starting sequence
                                                          // - State 1: Playing the sequence 
                                                          // - State 2: Waiting user input response
                                                          // - State 3: Game is over! Awaiting user to press green to continue
                                                        
int score = 0;                                            // Keeps track of the score
int sequence[101];                                        // Keeps track of the sequence
int buttonPressed[4] = {false, false, false, false};      // State of each button

int playerSequenceIndex = 0;                              // When the user is playing back the sequence, this keeps track of where in the sequence they are

/*
 * setup
 * --
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
  
  delay(1000);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {              // Use softwareSerial to communicate with mp3. If we have trouble,
    Serial.println(F("Unable to begin:"));                // print to the serial monitor so we can see.
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  } else {
    Serial.println(F("DFPlayer Mini online."));          
  }

  delay(1000);
  
  myDFPlayer.volume(20);                                   // Set volume value. From 0 to 30
 
  playAudio(1);                                            // Play the first mp3! Exciting stuff

  delay(240);                                              // This delay and digital write is timed to turn each light on and off
  for (int i = 2; i < 6; i ++) {                           // to match up with the sound effects
    for (int j = 0; j < (i == 5 ? 14 : 5); j ++) {         // There's an operation in there called the ternary operator.
      digitalWrite(i, HIGH);                               // If we're on the last LED (i.e. led 5) loop more times so we can time it with the music
      delay(50);
      digitalWrite(i, LOW);
      delay(50);
    }
  }
  delay(5000);
  state = 1;                                               // We're all set with this state. Let's set the state to 1 to start the sequence playing
}

/*
 * loop
 * --
 * The loop function is called continously - meaning, once it reaches the end, it'll do exactly as 
 * the name suggests. Loop and call the function again! Note that if you have delays() in this function, it means
 * each loop will take longer.
 */
void loop()
{
  if (state == 1) {                                        // This is where we'll play the sequence to the user
    Serial.println(score);
    for (int i = 0; i < score + 1; i++) {                  // The number of tones played is one more than the score
      playAudio(sequence[i]);                              // Play the tone as defined in our initial 100 tones.
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
                                                           
        playAudio(i);                                      
        digitalWrite(i, HIGH);
        delay(450);
        digitalWrite(i, LOW);
      
        if (sequence[playerSequenceIndex] == i) {
          playerSequenceIndex += 1;
          if (playerSequenceIndex > score) {               // That's all the buttons they need to play!
                                               
             playAudio(6);
             delay(800);
             if (score < MAX_SCORE) {
               score += 1;
               state = 1;                                  // We've updated the state, and now we're returning to the toy playing the sequence
             } else {
               playScoreSound(MAX_SCORE);                  // Gasp! They've reached 100! That's the highest possible score!
               playAudio(37);
               delay(3000);
               state = 3;
             }
          }                                                
        } else {
          state = 3;                                       // Player has lost! Update the state to now be in the 'waiting for reset'
          playAudio(7); 
          delay(200);
          for (int k = 2; k < 6; k ++) {
            digitalWrite(7-k, HIGH);
            delay(200);
            digitalWrite(7-k, LOW);
          }
          delay(3000);
          
          playScoreSound(score);
          
          playAudio(37);
          delay(2500);
        }
        
      } else if (digitalRead(i+4) == HIGH && buttonPressed[i-2] == true) {
        buttonPressed[i-2] = false;                        // Part of the debouncing system as mentioned above
      }
    }
  }

  if (state == 3) {                                        // Waiting for player to press 
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    if (digitalRead(6) == LOW || digitalRead(7) == LOW || digitalRead(8) == LOW || digitalRead(9) == LOW) {
      playerSequenceIndex = 0;
      score = 0;
      state = 1;
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      delay(1000);
    }
  }
}

/*
 * generate sequence
 * --
 * helper function that generates a sequence of 100 random tones
 */
void generateSequence() {
  randomSeed(analogRead(0));                              // Nothing is connected to pin A0, which will produce noise. 
                                                          // We can use this noise to generate a random number.
    
  for (int i = 0; i < MAX_SCORE + 1; i++) {               // Pre-set 100 random tones to be our sequence
    sequence[i] = random(2, 6);
  }
}

/*
 * play score sound
 * --
 * helper function that plays the audio file of the player's score
 * when the number gets larger than 19, the sounds are combined 
 * e.g. a voice recording of 20 + a voice recording of 4
 * when the number gets to 100, we play the final celebratory score
 */
void playScoreSound(int s) {
  if (s < 20) {
    playAudio(s + 8);
    delay(1500);
  } else if (s < 100) {
    int tens = s / 10;
    int ones = s % 10;
    playAudio(tens + 26);
    delay(800);
    if (ones != 0) {
      playAudio(ones + 8);
      delay(1500);
    }
  } else if (s == MAX_SCORE) {
    playAudio(36);
    delay(10000);
  }
}

void playAudio(int s) {
  myDFPlayer.play(s);
}
