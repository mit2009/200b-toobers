/***************************************************

 2.00b Toobers! 
 
 The 2022 Let's Play project - a simple simon-esque game.
 Full Source and README can be found here: https://github.com/mit2009/200b-toobers
 Hope you enjoy!
 
 Questions: [Victor Hung](vhung@mit.edu)
 Created for the 2022 MIT 2.00b Toy Product Design Class
 MIT License
 
 Parts adapted from the DFPlayer sample,
 by [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 ----------------------------------------------------
 
 This file is a work in progress.
 Plenty more documentation coming soon! I promise!
 - Victor
 *skeptical "we'll see noises"*
 - Everyone else
 
 ****************************************************/

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11);                // RX, TX
DFRobotDFPlayerMini myDFPlayer;                         // Create myDFPlayer of the DFPlayer Class
void printDetail(uint8_t type, int value);              

int state = 0;                                          // Create a variable to store the 'state' of the game
                                                        // - State 0: Game is playing starting sequence
                                                        // - State 1: Playing the sequence 
                                                        // - State 2: Waiting user input response
                                                        // - State 3: Game is over! Awaiting user to press green to continue
                                                        
int score = 0;                                          // Keeps track of the score
int sequence[100];                                      // Keeps track of the sequence
int buttonPressed[4] = {false, false, false, false};    // State of each button

int playerSequenceIndex = 0;                            // When the user is playing back the sequence, this keeps track of where in the sequence they are

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  for (int i = 2; i < 6; i++) {                         // Set inputs 2, 3, 4, 5 to be OUTPUT pins (LEDs)           
    pinMode(i, OUTPUT);
  }
  
  for (int i = 6; i < 10; i++) {                        // Set inputs 6, 7, 8, 9 to be INPUT pins (Buttons)
    pinMode(i, INPUT_PULLUP);
  }

  randomSeed(analogRead(0));                            // Nothing is connected to pin A0, which will produce noise. 
                                                        // We can use this noise to generate a random number.
    
  for (int i = 0; i < 100; i++) {
    int randomNumber = random(2, 6);
    if (i > 0) {
      if (randomNumber == sequence[i-1]) {
        randomNumber = random(2, 6);
      }
    }
    sequence[i] = random(2, 6);
  }
  
  Serial.println();
  Serial.println(F("Starting 2.00b Simon!"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {              // Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);     //Play the first mp3

  // Startup Lights
  delay(120);
  for (int i = 2; i < 6; i ++) {
    digitalWrite(i, HIGH);
    delay(400);
    digitalWrite(i, LOW);
  }
  delay(8000);
  state = 1;
}

void loop()
{
  // play the sequence
  if (state == 1) {
    for (int i = 0; i < score + 1; i++) {
      myDFPlayer.play(sequence[i]);
      digitalWrite(sequence[i], HIGH);
      delay(400);
      digitalWrite(sequence[i], LOW);
      delay(100);
    }
    playerSequenceIndex = 0;                // reset the player sequence number
    state = 2;                              // move to the next sequence
  }

  // wait for user input
  if (state == 2) {
    for (int i = 2; i < 6; i ++) {
      if (digitalRead(i+4) == LOW && buttonPressed[i-2] == false) {
        buttonPressed[i-2] = true;
        myDFPlayer.play(i);
        digitalWrite(i, HIGH);
        delay(450);
        digitalWrite(i, LOW);
      
        if (sequence[playerSequenceIndex] == i) {
          playerSequenceIndex += 1;
          if (playerSequenceIndex > score) {    // that's all the sequences they need to play!
             score += 1;
             myDFPlayer.play(6);
             delay(800);
             state = 1;
          }
        } else {
          state = 3;                            // oh no you've lost
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
        }
        
      } else if (digitalRead(i+4) == HIGH && buttonPressed[i-2] == true) {
        buttonPressed[i-2] = false;
      }
    }
  }

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
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
