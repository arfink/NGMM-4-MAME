# NGMM-4-MAME
Emulate a Neo Geo Mini Marquee and coin counter using Arduino and MAME

This software is in two parts. One part runs on an Arduino Uno, the other part is meant to run on a Linux machine with MAME and Python. This software has been tested with Python 2.7.12 and Mame 0.184. I believe that any version of MAME that supports the -output option should work here. 

To run, first plug in the Arduino, then run the python script with a simple "python mame". Keep in mind that you will likely have to edit the script to point to the correct device location.

For hardware, the Arduino expects LEDs on pins 2-5 for the Mini Marquee lamps. You can either hook up a single LED with a resistor or a more complicated setup with a transistor to drive multiple LEDs per Mini Marquee. For the counter, a pair of 74HC595 shift registers is used to drive a pair of 7 segment displays. Serial is on pin 8, latch on pin 9, and clock on pin 10.

I'm working on a simple reference schematic for this design which will come later. 
