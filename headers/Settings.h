#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Settings {
public:
    Settings();
    ~Settings();
    const static int WINDOW_WIDTH = 1400;
    const static int WINDOW_HEIGHT = 800;
    const static int TIMESCALE = 10;
    const static int TILESIZE = 32;
    bool playerColliding = true;
};
