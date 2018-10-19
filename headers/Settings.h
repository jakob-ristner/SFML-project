#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct keyMapping {
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;

    sf::Keyboard::Key openConsole;

    sf::Keyboard::Key spell1;
    sf::Keyboard::Key spell2;
    sf::Keyboard::Key spell3;
    sf::Keyboard::Key spell4;
    sf::Keyboard::Key spell5;
    sf::Keyboard::Key spell6;
    sf::Keyboard::Key spell7;
    sf::Keyboard::Key spell8;
    sf::Keyboard::Key spell9;

    sf::Keyboard::Key useSpell;
};

//defaultMapping.left  = sf::Keyboard::Key::A;
//defaultMapping.right = sf::Keyboard::Key::D;
//defaultMapping.up    = sf::Keyboard::Key::W;
//defaultMapping.down  = sf::Keyboard::Key::S;
//
//defaultMapping.openConsole = sf::Keyboard::Key::F1;
//
//defaultMapping.spell1 = sf::Keyboard::Key::Num1;
//defaultMapping.spell2 = sf::Keyboard::Key::Num2;
//defaultMapping.spell3 = sf::Keyboard::Key::Num3;
//defaultMapping.spell4 = sf::Keyboard::Key::Num4;
//defaultMapping.spell5 = sf::Keyboard::Key::Num5;
//defaultMapping.spell6 = sf::Keyboard::Key::Num6;
//defaultMapping.spell7 = sf::Keyboard::Key::Num7;
//defaultMapping.spell8 = sf::Keyboard::Key::Num8;
//defaultMapping.spell9 = sf::Keyboard::Key::Num9;
//
//defaultMapping.useSpell = sf::Keyboard::Key::Space;


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

 
    int TIMESCALE = 10;
    int TILESIZE = 32;
  
    bool playerColliding = true;

    keyMapping keyMap;
    int resolutions[7][2] = { {800, 600}, 
                              {1024, 768}, 
                              {1280, 960}, 
                              {1366, 768}, 
                              {1600, 900}, 
                              {1680, 1050}, 
                              {1920, 1080} 
                            };

    int selectedResolution = 4;
    int WINDOW_WIDTH = resolutions[selectedResolution][0];
    int WINDOW_HEIGHT = resolutions[selectedResolution][1];
};

extern Settings settings;
