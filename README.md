# GNSSSimulator



The goal of this program is to create a simulation enviroment which is capable of calculating PseudoRanges with additional variable errors - both deterministic and stohastic - and be able to handle various RAIM algorithms in the future.

Build instructions:

  - Build the 64-bit GPSTK library(https://github.com/SGL-UT/GPSTk) using CMAKE (Tested on 3.9.1) with 14 2015 Win64 generator
  - Include source files from GPSTK and the previously built library in Linker
  - Set Project Build Configuration Manager for x64

# Current Features

- The program uses GPSTK to parse RINEX navigation and observation files and stores all the neccesary satellite data, including position in transmit time.
- It can read a template Trajectory file which contains the coordinates and GPS timestamps for a Rover reference.
- Calculates absolute-"pseudo"range and stores it in a RINEX observation file.
