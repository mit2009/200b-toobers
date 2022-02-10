# 2.00b Toobers!
2.00b Let's Play Project - A Simple Simon-says-esque Game!

![toobers-three-01](https://user-images.githubusercontent.com/276204/151922931-3098fd76-6870-4891-96a3-2523f05bd8a4.png)

## Overview

Hello! Toobers is a simon-esque toy used for teaching in [MIT's 2.00b Toy Product Design](https://web.mit.edu/2.00b/www) Class. The goal of this project is to quickly get started and comfortable with making things and getting a quick overview of how one might put a toy together. The early parts are focused on electronics and prototyping, followed by some soldering and CAD work for the housing.

## Toobers Setup Instructions

The Toobers instructions can be found here [on the 2.00b Website!](http://web.mit.edu/2.00b/www/toobers/index.html)

## Copying sounds and Dotfiles

Copying sounds to the microSD card can be tricky. There are currently two known issues:

1. When sounds are copied over on a Mac, often times a dotfile is left there, causing the player to mis-order the files. To remove these dotfiles, you can run `dot_clean /Volumes/Untitled/1` (or on the appropriate folder/directory where the sound files are stored.) 

2. While this may no longer be an issue, reading online posts have suggested that DFPlayer library currently uses timestamps of a file to determine the file ordering (i.e. the 1st file is the oldest file, 2nd is 2nd oldest, etc.) a script has been made to copy a large number of files over in a sequential order. This is a temporary solution to a permanent problem.

To use this script, clone this repo (or download it by going to code > download zip), then (on a Mac) open terminal, and navigate to the `scripts` folder. Plug in the microSD card you wish to use, run `sh copy.sh`, type any key, and you should see a series of status messages. Leave the program running, eject the microSD card, plop in another one, and hit any key on the keyboard again (you may have to try multiple times, or wait until the drive is accessed). At the end of this transfer, the `dot_clean` command is also run, just in case any dotfiles were created.

If the name of the volume for the SD card is NOT Untitled, you'll have to change that in `copy.sh`, which you can open with any text editor.

## Miscellaneous

The software has been tested on an Arduino Uno, using the lovely [DFPlayer](https://www.dfrobot.com/product-1121.html) from DFRobot. 

More details coming soon!
