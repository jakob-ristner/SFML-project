# SFML-project
A project using sfml (and a bit of Python) to develop a 2D game in C++.

## Python Dependencies
* Pytmx
* Pygame

## Compilation
Just run *make* in the repo's root directory.

## Map Pre-parsing
Is done through a python script which will take a given tmx file
and convert it to a folder. In the folder there will be two files.
One is a new .tmx file which contains all the texture data and the
other contains the object data which kan then be interpreted by the
game.
### args
* input path (name of .tmx file)
* output path (name of folder that will be created)

## Controls:
* W,A,S,D - Walking
* Space - Cast spell
* 1-9 - Switch active spell
* §/F1 - Open developer console
* Escape - Pause

## Dev console commands:
x and y can always be any numbers, int or floating point.
### noclip
Toggles player collision with walls.
### setcolor *target* *r* *g* *b*
Sets the color of the given interface. Availile targets are:
* uigrid
### setplayerval *attribute* *amount*
Sets a given attribute of the player to a value. Availible attributes are:
* hp
* mana
* maxHp
* maxMana
* speedmult - *Multiplier of the players movement speed*
### setvisible *target* *bool*
Sets the visibility of the given interface. Availible targets are:
* uigrid
### setxlines uigrid *amount*
Sets the amount of vertical lines in the uigrid.
### setylines uigrid *amount*
Sets the amount of horizontal lines in the uigrid.
### spawn *npc* *x* *y*
Spawns a given npc on the given coordinates. Availible npcs are:
* slime
### tp *target* *x* *y*
Teleports the target to given coordinate. Availible targets are: 
* player
