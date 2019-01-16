#!/usr/bin/python
from os import listdir, system
from sys import argv

if '-c' in argv:
    sysout = 'g++ -c main.cpp '
    classes = [x[:-4] for x in listdir('./classes') if x[-4:] == '.cpp']
    for classname in classes:
        sysout += ("./classes/" + classname + ".cpp ")
    sysout += "./libs/src/TMXParser.cpp "
    sysout += "./libs/src/TSXParser.cpp "
    system(sysout[:-1])
    sysout = "g++ main.o "
    for classname in classes:
        sysout += classname + ".o "
    sysout += "TMXParser.o "
    sysout += "TSXParser.o "
    sysout += "-o sfml-app.out -lsfml-graphics -lsfml-window -lsfml-system"
    system(sysout)
    sysout = "mv main.o "
    sysout += "TMXParser.o "
    sysout += "TSXParser.o "
    for classname in classes:
        sysout += classname + ".o "
    sysout += "./obj/"
    system(sysout)
if '-r' in argv:
    system("./sfml-app.out")


