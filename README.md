# COMP 498 - Assignment 1
Steve Ferreira, 27477546  
Section: Winter 2018 - GG  
Date: January 23, 2018  

**I certify that this submission is my original work and meets the Faculty's Expectations of Originality.**

## Prequisits
- OpenCV
- C++ 11
- CMake
- Make

## Compilation instructions

**This project uses the C++11 standard, and you will need a recent compiler capable of supporting these features.**

This project uses CMake >=3.5 (https://cmake.org/) to generate build files for any platform. It can be installed on Linux or macOS using a package manager, or Windows using the official installer. Ensure it is added to your system PATH and accessible via command line.

Then, CMake can be used in the command line to generate build files for any environment desired.

1. `cd [path to assignment]`
2. `mkdir build`
3. `cd build`
4. `cmake -G "your generator here" ..`
    - Run `cmake -G` to see a list of possible generators, eg. `Xcode`, `Unix Makefiles`, versions of Visual Studio, etc.
5. Build the project using whichever build system you chose.

## Results
Running the program will display three images per mosaic provided. The original color image is displayed along side the demosaiced color image, and a comparison image to highlight the introduced artifacts.

![alt text][full]

A second set of images is displayed to show the improved interpolation method from Part 2. A close up comparison can be found below.
- Part 1: Linear interpolation using filter2D:  
	![alt text][p1-closeup]
- Part 2: Modified linear interpolation and median filtering:  
	![alt text][p2-closeup]

[full]: https://raw.githubusercontent.com/Shmeve/comp498-a1-demosaicing/master/images/readme/part1-results.png?token=AKNuRNEv2Y6Us6AiE9_9LYnsRuW17-e5ks5acOPLwA%3D%3D
[p1-closeup]: https://raw.githubusercontent.com/Shmeve/comp498-a1-demosaicing/master/images/readme/part1-differences.png?token=AKNuREvPXYovTfHhK6BXs_bbAX096nLsks5acOPiwA%3D%3D
[p2-closeup]: https://raw.githubusercontent.com/Shmeve/comp498-a1-demosaicing/master/images/readme/part2-differences.png?token=AKNuRIC3n3nMgXnPhJh5ick5HncNIEaNks5acOPhwA%3D%3D

## Notes
This assignment has been tested on Linux, using OpenCV 3.4.0, CMake 3.10.2, Make 4.2.1
