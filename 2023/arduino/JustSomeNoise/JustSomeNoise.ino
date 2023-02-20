/***************************************************

 2.00b Toobers! 
 
 The 2023 Let's Play project - a simple simon-esque game.
 Full Source and README can be found here: https://github.com/mit2009/200b-toobers
 Hope you enjoy!
 
 Created for the 2023 MIT 2.00b Toy Product Design Class
 Questions?: hit us up on #ask-the-tas on Slack
 Cheers, [Victor Hung](vhung@mit.edu)
 MIT License
 
 Parts adapted from the DFPlayer sample,
 by [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 ****************************************************/

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(3, 2);                    // Recieve Pin (RX), Transmit Pin (TX)
DFRobotDFPlayerMini myDFPlayer;                           // Create myDFPlayer of the DFPlayer Class
              // When the user is playing back the sequence, this keeps track of where in the sequence they are

/*
 * setup
 * --
 * The setup() function is called when a sketch starts. Use it to initialize variables, pin modes, start using libraries, etc. 
 * This function will only run once, after each powerup or reset of the Arduino board.
 */
void setup() {
  
  mySoftwareSerial.begin(9600);                           // Initiate communication with the DFPlayer
  Serial.begin(115200);                                   // Mostly used for debugging

  Serial.println(F("Starting 2.00b Simon!"));             // Print to serial monitor that we're starting!       
  
  delay(1000);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {              // Use softwareSerial to communicate with mp3. If we have trouble,
    Serial.println(F("Unable to begin:"));                // print to the serial monitor so we can see.
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  } else {
    Serial.println(F("DFPlayer Mini online."));          
  }

  
  myDFPlayer.volume(20);                                   // Set volume value. From 0 to 30
  playAudio(1);                                            // Play the first mp3! Exciting stuff
}

void loop() {

}

void playAudio(int s) {
  myDFPlayer.play(s);
}
