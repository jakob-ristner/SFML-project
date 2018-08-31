#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Settings {
public:
    Settings();
    ~Settings();
    const static int WINDOW_WIDTH = 1920;
    const static int WINDOW_HEIGHT = 1080;
    const static int TIMESCALE = 10;
    const static int TILESIZE = 32;
    bool playerColliding = true;
};
