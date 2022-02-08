# 2.00b Toobers!
2.00b Let's Play Project - A Simple Simon-says-esque Game!

![toobers-three-01](https://user-images.githubusercontent.com/276204/151922931-3098fd76-6870-4891-96a3-2523f05bd8a4.png)

## Copying sounds
Because the DFPlayer library currently used uses timestamps of a file to determine the file ordering (i.e. the 1st file is the oldest file, 2nd is 2nd oldest, etc.) a script has been made to copy a large number of files over in a sequential order. This is a temporary solution to a permanent problem.

To use this script, clone this repo (or download it by going to code > download zip), then (on a Mac) open terminal, and navigate to the `scripts` folder. Plug in the microSD card you wish to use, run `sh copy.sh`, type any key, and you should see a series of status messages. Leave the program running, eject the microSD card, plop in another one, and hit any key on the keyboard again (you may have to try multiple times, or wait until the drive is accessed).

If the name of the volume for the SD card is NOT Untitled, you'll have to change that in `copy.sh`, which you can open with any text editor.

Software tested on an Arduino Uno, using the lovely [DFPlayer](https://www.dfrobot.com/product-1121.html) from DFRobot. 

More details coming soon!
