Orbit Test
==========

Basic Orbit Simulation in C++ using SDL.

This program heavily uses tutorial code.

This was written with the intent to find out how difficult it would be to write a C++ program to simulate and display an object orbiting a planet. 

Gravity is only applied to the object. The planet is a stationary object.

# Controls

W will increase speed in the direction the object is moving. 

S will decrease speed.

Disabled code exists in the cpp file to include another planet and bounce the object off the sides of the screen.
Uncomment that code to enable those features.

# Compilation

Use the command
```
$ g++ sdltest.cpp `sdl-config --cflags --libs`
```
in the main directory

# Running

Use the command
```
./a.out
```
in the main directory

# Bugs

When the object gets too close to the center of the planet rounding errors cause the object to speed up and sometimes crash the program.

Going off screen horizontally will cause the object to be drawn on the opposite side of the screen, even though gravity is still applied
as if the object were in the correct position.
