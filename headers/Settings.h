#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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

    int WINDOW_WIDTH = 1600;
    int WINDOW_HEIGHT = 900;
 
    int TIMESCALE = 10;
    int TILESIZE = 32;
  
    bool playerColliding = true;
};

extern Settings settings;
