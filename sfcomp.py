#!/usr/bin/python
from os import listdir, system, path, makedirs
from sys import argv

repo_dir = path.dirname(path.abspath(__file__))
obj_dir = repo_dir + "\\obj"

if not path.exists(obj_dir):
    makedirs(obj_dir)

if '-c' in argv:
    sysout = 'g++ -c '
    classes = [x[:-4] for x in listdir('./classes') if x[-4:] == '.cpp']
    for classname in classes:
        sysout += ("./classes/" + classname + ".cpp ")
    sysout += "./libs/src/TMXParser.cpp "
    sysout += "./libs/src/TSXParser.cpp "
    sysout += "-Ilibs/include -Llibs/lib -lsfml-graphics -lsfml-window -lsfml-system"
    system(sysout[:-1])
    sysout = "g++ "
    for classname in classes:
        sysout += classname + ".o "
    sysout += "TMXParser.o "
    sysout += "TSXParser.o "
    sysout += "-o sfml-app.exe -Ilibs/include -Llibs/lib -lsfml-graphics -lsfml-window -lsfml-system"
    system(sysout)
    sysout = "move *.o "
    sysout += obj_dir
    system(sysout)
if '-r' in argv:
    system(".\\sfml-app.exe")
