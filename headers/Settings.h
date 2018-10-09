#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct keyMapping {
    int left;
    int right;
    int up;
    int down;

    int openConsole;

    int spell1;
    int spell2;
    int spell3;
    int spell4;
    int spell5;
    int spell6;
    int spell7;
    int spell8;
    int spell9;

    int useSpell;
}

keyMapping defaultMapping;
defaultMapping.left  = sf::Keyboard::Key::A;
defaultMapping.right = sf::Keyboard::Key::D;
defaultMapping.up    = sf::Keyboard::Key::W;
defaultMapping.down  = sf::Keyboard::Key::S;

defaultMapping.openConsole = sf::Keyboard::Key::F1;

defaultMapping.spell1 = sf::Keyboard::Key::Num1;
defaultMapping.spell2 = sf::Keyboard::Key::Num2;
defaultMapping.spell3 = sf::Keyboard::Key::Num3;
defaultMapping.spell4 = sf::Keyboard::Key::Num4;
defaultMapping.spell5 = sf::Keyboard::Key::Num5;
defaultMapping.spell6 = sf::Keyboard::Key::Num6;
defaultMapping.spell7 = sf::Keyboard::Key::Num7;
defaultMapping.spell8 = sf::Keyboard::Key::Num8;
defaultMapping.spell9 = sf::Keyboard::Key::Num9;

defaultMapping.useSpell = sf::Keyboard::Key::Space;


// Supported resolutions:
// 800x600
// 1024x768
// 1280x960
// 1366x768
// 1600x900
// 1680x1050
// 1920x1080

class Settings {
public:
    Settings();
    ~Settings();

    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;
 
    int TIMESCALE = 10;
    int TILESIZE = 32;
  
    bool playerColliding = true;

    keyMapping keyMap = defaultMapping;
};

extern Settings settings;
