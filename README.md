# SFML-project
A project using sfml (and a bit of Python) to develop a 2D game in C++.

## Python Dependencies
* Pytmx
* Pygame

## Controls:
* W,A,S,D - Walking
* Space - Cast spell
* 1, 2 - Switch active spell
* § - Open developer console

## Dev console commands:
x and y can always be any numbers, int or floating point.
### noclip
Toggles player collision with walls.
### tp *target* *x* *y*
Teleports the target to given coordinate. Availible targets are: 
* player
### spawn *npc* *x* *y*
Spawns a given npc on the given coordinates. Availible npcs are:
* slime
### setvisible *target* *bool*
Sets the visibility of the given interface. Availible interfaces are:
* uigrid
### setxlines uigrid *amount*
Sets the amount of vertical lines in the uigrid.
### setylines uigrid *amount*
Sets the amount of horizontal lines in the uigrid.
### setcolor *target* *r* *g* *b*
Sets the color of the given interface. Availile interfaces are:
* uigrid
